// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "UntitledNPC.generated.h"

UCLASS()
class UNTITLED_API AUntitledNPC : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AUntitledNPC();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "NPC Interaction")
	virtual void Interact();
	
};
