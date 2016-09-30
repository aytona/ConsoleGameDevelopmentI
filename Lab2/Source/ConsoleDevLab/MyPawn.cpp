// Fill out your copyright notice in the Description page of Project Settings.

#include "ConsoleDevLab.h"
#include "MyPawn.h"

// Sets default values
AMyPawn::AMyPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Control this player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
	// Template of method with parament of what it is going to be shown in the editor
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	
	UCameraComponent* OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("OurCamera"));
	OurVisibleComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("OurVisibleComponent"));

	OurCamera->SetupAttachment(RootComponent);
	OurCamera->SetRelativeLocation(FVector(-250.0f, 0.0f, 250.0f));
	OurCamera->SetRelativeRotation(FRotator(-45.0f, 0.0f, 0.0f));

	OurVisibleComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	float CurrentScale = OurVisibleComponent->GetComponentScale().X;

	if (bGrowing)
		CurrentScale += DeltaTime;
	else
		CurrentScale -= (DeltaTime * 0.5f);
	CurrentScale = FMath::Clamp(CurrentScale, 1.0f, 2.0f);
	OurVisibleComponent->SetWorldScale3D(FVector(CurrentScale));

	if (!CurrentVelocity.IsZero())
	{
		FVector NewLocation = GetActorLocation() + (CurrentVelocity * DeltaTime);
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	InputComponent->BindAction("Grow", IE_Pressed, this, &AMyPawn::StartGrowing);
	InputComponent->BindAction("Grow", IE_Released, this, &AMyPawn::StopGrowing);

	InputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	InputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
	InputComponent->BindAxis("MoveZ", this, &AMyPawn::Move_ZAxis);
}

void AMyPawn::Move_XAxis(float value)
{
	CurrentVelocity.X = FMath::Clamp(value, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_YAxis(float value)
{
	CurrentVelocity.Y = FMath::Clamp(value, -1.0f, 1.0f) * 100.0f;
}

void AMyPawn::Move_ZAxis(float value)
{
	CurrentVelocity.Z = FMath::Clamp(value, -1.0f, 2.0f) * 100.0f;
}

void AMyPawn::StartGrowing()
{
	bGrowing = true;
}

void AMyPawn::StopGrowing()
{
	bGrowing = false;
}


