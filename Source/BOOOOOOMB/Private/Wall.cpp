#include "Wall.h"


AWall::AWall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WallType = EWallType::WTE_Static;
}

AWall::AWall(EWallType& InWallType)
{
	WallType = InWallType;
	switch (WallType)			
	{
		case EWallType::WTE_Static:
		case EWallType::WTE_Destroyable:
			PrimaryActorTick.bCanEverTick = false;
			break;
		case EWallType::WTE_Movable:
			PrimaryActorTick.bCanEverTick = true;
			break;
	}
}

// Called when the game starts or when spawned
void AWall::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

