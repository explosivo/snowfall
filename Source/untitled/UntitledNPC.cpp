// Fill out your copyright notice in the Description page of Project Settings.

#include "untitled.h"
#include "UntitledNPC.h"


// Sets default values
AUntitledNPC::AUntitledNPC()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AUntitledNPC::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUntitledNPC::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AUntitledNPC::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}
