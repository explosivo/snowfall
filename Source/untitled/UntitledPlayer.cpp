#include "untitled.h"
#include "UntitledPlayer.h"
#include "UntitledNPC.h"


// Sets default values
AUntitledPlayer::AUntitledPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom);
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void AUntitledPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUntitledPlayer::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
}

// Called to bind functionality to input
void AUntitledPlayer::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("Interact", IE_Pressed, this, &AUntitledPlayer::Interact);

	InputComponent->BindAxis("MoveForward", this, &AUntitledPlayer::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AUntitledPlayer::MoveRight);

	InputComponent->BindAxis("Zoom", this, &AUntitledPlayer::ZoomCamera);
	InputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	InputComponent->BindAxis("TurnRate", this, &AUntitledPlayer::TurnAtRate);
	InputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	InputComponent->BindAxis("LookUpRate", this, &AUntitledPlayer::LookUpAtRate);
}

void AUntitledPlayer::TurnAtRate(float Rate)
{
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void AUntitledPlayer::LookUpAtRate(float Rate)
{
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void AUntitledPlayer::MoveForward(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AUntitledPlayer::MoveRight(float Value)
{
	if ((Controller != NULL) && (Value != 0.0f))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AUntitledPlayer::ZoomCamera(float Value)
{
	CameraBoom->TargetArmLength += Value;
}

AActor* AUntitledPlayer::CheckForInteractions()
{
	AActor *HitActor = NULL;
	FVector Start = GetActorLocation();
	FVector End = Start + FRotationMatrix(GetActorRotation()).GetScaledAxis(EAxis::X) * 300;
	FHitResult HitData(ForceInit);
	bool FoundObject = false;

	if (!GetWorld())
	{
		return NULL;
	}

	//DrawDebugLine(GetWorld(), Start, End, FColor::Red);

	FCollisionQueryParams TraceParams(FName(TEXT("Interactions Trace")), true, NULL);
	TraceParams.bTraceComplex = false;
	TraceParams.bReturnPhysicalMaterial = false;
	TraceParams.AddIgnoredActor(this);
	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	GetWorld()->LineTraceSingleByObjectType(HitData, Start, End, ObjectParams, TraceParams);
	HitActor = HitData.GetActor();

	return HitActor;
}

void AUntitledPlayer::Interact()
{
	AActor *actor = CheckForInteractions();
	if (actor != NULL)
	{
		if (actor->IsA(AUntitledNPC::StaticClass()))
		{
			AUntitledNPC *npc = Cast<AUntitledNPC>(actor);
			npc->Interact();
		}
	}
}
