#pragma once

#include "FlareWeapon.h"
#include "FlareProjectile.generated.h"


UCLASS(Blueprintable, ClassGroup = (Flare, Ship), meta = (BlueprintSpawnableComponent))
class AFlareProjectile : public AActor
{
public:

	GENERATED_UCLASS_BODY()

public:

	/*----------------------------------------------------
		Public methods
	----------------------------------------------------*/

	virtual void PostInitializeComponents() override;

	/** Properties setup */
	void Initialize(class UFlareWeapon* Weapon, const FFlareShipComponentDescription* Description, FVector ShootDirection, FVector ParentVelocity);

	/** Impact happened */
	UFUNCTION()
	void OnImpact(const FHitResult& HitResult, const FVector& ImpactVelocity);


protected:

	/*----------------------------------------------------
		Protected data
	----------------------------------------------------*/

	/** Impact sound */
	UPROPERTY()
	USoundCue*                               ImpactSound; // TODO M3 : Move to characteristic (weapon description)

	/** Damage sound */
	UPROPERTY()
	USoundCue*                               DamageSound; // TODO M3 : Move to characteristic (weapon description)

	/** Mesh component */
	UPROPERTY()
	UStaticMeshComponent*                    ShellComp;

	/** Movement component */
	UPROPERTY()
	UProjectileMovementComponent*            MovementComp;

	/** Special effects on explosion */
	UPROPERTY()
	UParticleSystem*                         ExplosionEffectTemplate;

	/** Special effects on flight */
	UPROPERTY()
	UParticleSystem*                         FlightEffectsTemplate;

	// Flight effects
	UParticleSystemComponent*                FlightEffects;

	/** Burn mark decal */
	UPROPERTY()
	UMaterialInterface*                      ExplosionEffectMaterial;

	// Shell data
	FVector                                  ShellDirection;
	const FFlareShipComponentDescription*    ShellDescription;
	int32 ShellPower;
	float ShellMass;

};
