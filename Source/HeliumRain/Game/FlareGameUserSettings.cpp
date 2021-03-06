
#include "../Flare.h"
#include "FlareGameUserSettings.h"


/*----------------------------------------------------
	Constructor
----------------------------------------------------*/

UFlareGameUserSettings::UFlareGameUserSettings(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
}

void UFlareGameUserSettings::SetToDefaults()
{
	Super::SetToDefaults();

	ScreenPercentage = 100;

	UseCockpit = true;
	PauseGameInMenus = false;

	MusicVolume = 8;
	MasterVolume = 10;
}

void UFlareGameUserSettings::ApplySettings(bool bCheckForCommandLineOverrides)
{
	Super::ApplySettings(bCheckForCommandLineOverrides);
	FLOG("UFlareGameUserSettings::ApplySettings");
	SetScreenPercentage(ScreenPercentage);
}

void UFlareGameUserSettings::SetScreenPercentage(int32 NewScreenPercentage)
{
	FLOGV("UFlareGameUserSettings::SetScreenPercentage %d", NewScreenPercentage);
	ScreenPercentage = NewScreenPercentage;
	auto ScreenPercentageCVar = IConsoleManager::Get().FindConsoleVariable(TEXT("r.ScreenPercentage"));
	ScreenPercentageCVar->Set(ScreenPercentage, ECVF_SetByGameSetting);
}
