// Copyright Kristian Bakov 2024


#include "Player/AuraPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Input/AuraInputComponent.h"
#include "Interaction/TargetInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true;
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if(!CursorHit.bBlockingHit) return;

	LastTargetActor = ThisTargetActor;
	ThisTargetActor = Cast<ITargetInterface>(CursorHit.GetActor());

	HighlightTargetActor();
}


void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem =
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if(InputSubsystem)
	{
		InputSubsystem->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	
	AuraInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed,
		&ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
}

void AAuraPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AAuraPlayerController::HighlightTargetActor() const
{
	/**
	 * Line trace from cursor there are several scenarios
	 * A. Last actor is null && this actor is null
	 *		 - do nothing
	 *	B. Last actor is null && this actor is valid
	 *		 - highlight this actor
	 *	C. Last actor is valid && this actor is null
	 *		- unhighlight last actor
	 *	D. Both actors are valid but last actor != this actor
	 *		- unhighlight last actor and highlight this actor
	 *	E. Both actors are valid and last actor == this actor
	 *		- do nothing
	 */

	if(LastTargetActor == nullptr)
	{
		if(ThisTargetActor != nullptr)
		{
			//case b
			ThisTargetActor->HighlightActor();
		}
		else
		{
			//case a
			return;
		}
	}
	else // last actor is valid
	{
		if(ThisTargetActor == nullptr)
		{
			//case c
			LastTargetActor->UnhighlightActor();
		}
		else
		{
			if(LastTargetActor != ThisTargetActor)
			{
				//case d
				LastTargetActor->UnhighlightActor();
				ThisTargetActor->HighlightActor();
			}
			else
			{
				//case e
				return;
			}
		}
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("AbilityInputTagPressed"));
}

void AAuraPlayerController::AbilityInputTagReleased(const FGameplayTag InputTag)
{
	if(GetASC() == nullptr) return;
	GetASC()->AbilityInputTagReleased(InputTag);
}

void AAuraPlayerController::AbilityInputTagHeld(const FGameplayTag InputTag)
{
	if(GetASC() == nullptr) return;
	GetASC()->AbilityInputTagHeld(InputTag);
}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if(AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}
