#pragma once

#include "FlareSpacecraftDockingSystem.generated.h"

class AFlareSpacecraft;


/** Docking data */
struct FFlareDockingInfo
{
	bool                      Granted;
	bool                      Occupied;
	int32                     DockId;
	EFlarePartSize::Type      DockSize;
	AFlareSpacecraft*         Station;
	AFlareSpacecraft*         Ship;

	FVector                   LocalAxis;
	FVector                   LocalLocation;

	FFlareDockingInfo()
		: Granted(false)
		, Occupied(false)
		, DockId(-1)
		, Station(NULL)
	{}
};

/** Spacecraft docking system class */
UCLASS()
class HELIUMRAIN_API UFlareSpacecraftDockingSystem : public UObject
{

public:

	GENERATED_UCLASS_BODY()

public:

	/*----------------------------------------------------
		Public methods
	----------------------------------------------------*/

	virtual void TickSystem(float DeltaSeconds);

	/** Initialize this system */
	virtual void Initialize(AFlareSpacecraft* OwnerSpacecraft, FFlareSpacecraftSave* OwnerData);

	virtual void Start();

public:

	/*----------------------------------------------------
		System API
	----------------------------------------------------*/

	/** Get the list of docked ships */
	virtual TArray<AFlareSpacecraft*> GetDockedShips();

	/** Request a docking point */
	virtual FFlareDockingInfo RequestDock(AFlareSpacecraft* Ship, FVector PreferredLocation);

	/** Cancel docking */
	virtual void ReleaseDock(AFlareSpacecraft* Ship, int32 DockId);

	/** Confirm the docking from external ship */
	virtual void Dock(AFlareSpacecraft* Ship, int32 DockId);

	/** Get infos for a specific docking port */
	virtual FFlareDockingInfo GetDockInfo(int32 DockId);

	virtual bool HasAvailableDock(AFlareSpacecraft* Ship) const;

	virtual bool HasCompatibleDock(AFlareSpacecraft* Ship) const;

	virtual int GetDockCount() const;

	virtual bool IsGrantedShip(AFlareSpacecraft* ShipCanditate) const;

	virtual bool IsDockedShip(AFlareSpacecraft* ShipCanditate) const;

protected:

	/*----------------------------------------------------
		Protected data
	----------------------------------------------------*/

	UPROPERTY()
	AFlareSpacecraft*                               Spacecraft;
	FFlareSpacecraftSave*                           Data;
	FFlareSpacecraftDescription*                    Description;
	TArray<UActorComponent*>                        Components;

	// Dock data
	TArray <FFlareDockingInfo>       DockingSlots;

};
