#pragma once

#include "../Economy/FlareFactory.h"
#include "FlareFactoryCatalogEntry.generated.h"


UCLASS()
class UFlareFactoryCatalogEntry : public UDataAsset
{
	GENERATED_UCLASS_BODY()

public:

	/*----------------------------------------------------
		Public data
	----------------------------------------------------*/

	/** Factory data */
	UPROPERTY(EditAnywhere, Category = Content)
	FFlareFactoryDescription Data;

};