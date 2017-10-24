#include "LevelGenerator.h"

ALevelGenerator::ALevelGenerator()
{
	PrimaryActorTick.bCanEverTick = false;

	Seed = FMath::RandRange(0, INT32_MAX);

	Level = 3;

	for(uint8 i = 0; i < 8; i++)
		for(uint8 j = 0; j < 8; j++)
			Grid[i][j] = false;

	BaseDirection = EDirection::DE_UP;

	CurrentX = 0;
	CurrentY = 0;
}

ALevelGenerator::ALevelGenerator(const int32& InSeed)
{
	PrimaryActorTick.bCanEverTick = false;

	Seed = InSeed;

	Level = 3;

	for(uint8 i = 0; i < 8; i++)
		for(uint8 j = 0; j < 8; j++)
			Grid[i][j] = false;

	BaseDirection = EDirection::DE_UP;

	CurrentX = 0;
	CurrentY = 0;
}

void ALevelGenerator::GenerateWalls()
{
	GenerateStartingGrid();
	GenerateHilbertCurve(Level, BaseDirection);

	for (uint8 i = 0; i < 15; i++)
		for (uint8 j = 0; j < 15; j++)
			if(Grid[i][j])
				GetWorld()->SpawnActor<AWall>();

}

void ALevelGenerator::GenerateStartingGrid()
{
	switch (Seed % 4)
	{
		case 0:
			BaseDirection = EDirection::DE_UP;
			CurrentY = 0;
			CurrentX = 14;
			break;
		case 1:
			BaseDirection = EDirection::DE_LEFT;
			CurrentY = 0;
			CurrentX = 14;
			break;
		case 2:
			BaseDirection = EDirection::DE_RIGHT;
			CurrentY = 14;
			CurrentX = 0;
			break;
		case 3:
			BaseDirection = EDirection::DE_DOWN;
			CurrentY = 14;
			CurrentX = 0;
			break;
		Grid[CurrentY][CurrentX] = true;
	}
}

void ALevelGenerator::GenerateHilbertCurve(uint8 Level, EDirection Direction)
{
	if (Level == 1)
	{
		switch (Direction)
		{
		case EDirection::DE_LEFT:
			ConnectHilbert(EDirection::DE_RIGHT);
			ConnectHilbert(EDirection::DE_DOWN);
			ConnectHilbert(EDirection::DE_LEFT);
			break;
		case EDirection::DE_RIGHT:
			ConnectHilbert(EDirection::DE_LEFT);
			ConnectHilbert(EDirection::DE_UP);
			ConnectHilbert(EDirection::DE_RIGHT);
			break;
		case EDirection::DE_UP:
			ConnectHilbert(EDirection::DE_DOWN);
			ConnectHilbert(EDirection::DE_RIGHT);
			ConnectHilbert(EDirection::DE_UP);
			break;
		case EDirection::DE_DOWN:
			ConnectHilbert(EDirection::DE_UP);
			ConnectHilbert(EDirection::DE_LEFT);
			ConnectHilbert(EDirection::DE_DOWN);
			break;
		}
	}
	else
		switch (Direction)
		{
		case EDirection::DE_LEFT:
			GenerateHilbertCurve(Level - 1, EDirection::DE_UP);
			ConnectHilbert(EDirection::DE_RIGHT);
			GenerateHilbertCurve(Level - 1, EDirection::DE_LEFT);
			ConnectHilbert(EDirection::DE_DOWN);
			GenerateHilbertCurve(Level - 1, EDirection::DE_LEFT);
			ConnectHilbert(EDirection::DE_LEFT);
			GenerateHilbertCurve(Level - 1, EDirection::DE_DOWN);
			break;
		case EDirection::DE_RIGHT:
			GenerateHilbertCurve(Level - 1, EDirection::DE_DOWN);
			ConnectHilbert(EDirection::DE_LEFT);
			GenerateHilbertCurve(Level - 1, EDirection::DE_RIGHT);
			ConnectHilbert(EDirection::DE_UP);
			GenerateHilbertCurve(Level - 1, EDirection::DE_RIGHT);
			ConnectHilbert(EDirection::DE_RIGHT);
			GenerateHilbertCurve(Level - 1, EDirection::DE_UP);
			break;
		case EDirection::DE_UP:
			GenerateHilbertCurve(Level - 1, EDirection::DE_LEFT);
			ConnectHilbert(EDirection::DE_DOWN);
			GenerateHilbertCurve(Level - 1, EDirection::DE_UP);
			ConnectHilbert(EDirection::DE_RIGHT);
			GenerateHilbertCurve(Level - 1, EDirection::DE_UP);
			ConnectHilbert(EDirection::DE_UP);
			GenerateHilbertCurve(Level - 1, EDirection::DE_RIGHT);
			break;
		case EDirection::DE_DOWN:
			GenerateHilbertCurve(Level - 1, EDirection::DE_RIGHT);
			ConnectHilbert(EDirection::DE_UP);
			GenerateHilbertCurve(Level - 1, EDirection::DE_DOWN);
			ConnectHilbert(EDirection::DE_LEFT);
			GenerateHilbertCurve(Level - 1, EDirection::DE_DOWN);
			ConnectHilbert(EDirection::DE_DOWN);
			GenerateHilbertCurve(Level - 1, EDirection::DE_LEFT);
			break;
		}
}

void ALevelGenerator::ConnectHilbert(EDirection Direction)
{
	switch (Direction)
	{
	case EDirection::DE_LEFT:
		Grid[CurrentY][--CurrentX] = true;
		Grid[CurrentY][--CurrentX] = true;
		break;
	case EDirection::DE_RIGHT:
		Grid[CurrentY][++CurrentX] = true;
		Grid[CurrentY][++CurrentX] = true;
		break;
	case EDirection::DE_UP:
		Grid[++CurrentY][CurrentX] = true;
		Grid[++CurrentY][CurrentX] = true;
		break;
	case EDirection::DE_DOWN:
		Grid[--CurrentY][CurrentX] = true;
		Grid[--CurrentY][CurrentX] = true;
		break;
	}
}
