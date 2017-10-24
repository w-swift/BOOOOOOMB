#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

/** Four direction enum, used for rotate the U shape of Hilbert Curve. */
UENUM(BlueprintType)
enum class EDirection : uint8
{
	DE_UP = 0	UMETA(DisplayName = "UP"),
	DE_LEFT		UMETA(DisplayName = "LEFT"),
	DE_RIGHT	UMETA(DisplayName = "RIGHT"),
	DE_DOWN		UMETA(DisplayName = "DOWN")
};

/** 
 * User Hilbert Curve to generate random walls in level.
 * Default size is 8*8 Grid. Define by macro GRIDSIZE.
 */
UCLASS()
class BOOOOOOMB_API ALevelGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	/** Default Constructor. */
	ALevelGenerator();

	/** Constructor with give seed. */
	ALevelGenerator(const int32& InSeed);

private:
	/**
	 * Main recursive function to draw Hilbert Curve.
	 */
	void GenerateWalls();

	/**
	 * Calcute the starting grid of Hilbert Curve base from the direction of U shape.
	 */
	void GenerateStartingGrid();

	/**
	 * Main recursive function to draw Hilbert Curve.
	 * @param Level Current level of Hilbert Curve. Power of 2.
	 * @param Direction The direction which the U shape is facing to.
	 */
	void GenerateHilbertCurve(uint8 Level, EDirection Direction);

	/**
	 * Handle the curve of each singlej U shape, change Grid[][] state and Emplace WallArray.
	 * @param Direction The direction of U shape face to.
	 */
	void ConnectHilbert(EDirection Direction);

private:
	/** Generate random disable location with seed. */
	int32 Seed;

	/** The level of Hilbert Curve. Power of 2. */
	uint8 Level;
	
	/** The orientation of the base U shape face to. */
	EDirection BaseDirection;

	/** 
	 * Represent the Hilbert curve size is 8*8.
	 * true Grid has wall.
	 * false Grid is empty.
	 */
	bool Grid[15][15];

	/** The X value of current grid, represent column index. */
	int32 CurrentX;

	/** The Y value of current gird, represent row index. */
	int32 CurrentY;

	/** Save all the references of random walls. */
	TArray<class AWall*>AWallArray;
};
