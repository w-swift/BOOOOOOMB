#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Wall.generated.h"

/** 
 * Type of wall.
 * WTE_Static Common wall, invincible, can't move.
 * WTE_Destroyable Can be destroyed by taking damage, create new path.
 * WTE_Movable Floating wall constantly moving up and down.
 */
UENUM(BlueprintType)
enum class EWallType : uint8
{
	WTE_Static		UMETA(DisplaceName = "Static"), 
	WTE_Destroyable	UMETA(DisplaceName = "Destroyable"),
	WTE_Movable		UMETA(DisplaceName = "Movable")
};

/**
 * Base class of wall. Spawned by ALevelGenerator with different types, can be placed in level to block ways.
 */
UCLASS()
class BOOOOOOMB_API AWall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Default Constructor.
	AWall();

	/*
	 * Constructor with given wall type.
	 * @param InWallType The Type of wall.
	 */
	AWall(EWallType& InWallType);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// Type of wall.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wall")
	EWallType WallType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wall")
	class UBoxComponent* WallCollision;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wall")
	class UStaticMesh* WallMesh;
};
