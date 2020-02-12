// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Abilities/Ability.h"
#include "SubclassOf.h"
#include "DataTables/TopDownARPGCharacterStruct.h"
#include "TopDownARPGCharacter.generated.h"

USTRUCT()
struct FAbilityDataStruct : public FTableRowBase
{
	GENERATED_BODY()

public:
	FAbilityDataStruct() :Name("DefaultName"), Template(nullptr), Description("DefaultDescription") {}

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAbility> Template;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Description;

};

UCLASS(Blueprintable)
class ATopDownARPGCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ATopDownARPGCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns CursorToWorld subobject **/
	FORCEINLINE class UDecalComponent* GetCursorToWorld() { return CursorToWorld; }

	FORCEINLINE float GetHealth() { return Health; }

	/** A data table containing data for this character's abilities */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Gameplay)
	class UDataTable* AbilityDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay)
	TArray<UAbility*> AbilityInstances;

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** A decal that projects to the cursor location. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UDecalComponent* CursorToWorld;

	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UAbility>> AbilityTemplates;

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle CharacterStatsRow;

	UPROPERTY(EditDefaultsOnly)
	float MaximumHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Health;

	UFUNCTION()
	void TakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigateBy, AActor* DamageCauser);

	void Death();
};

