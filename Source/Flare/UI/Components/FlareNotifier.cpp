
#include "../../Flare.h"
#include "FlareNotifier.h"

#define LOCTEXT_NAMESPACE "FlareNotifier"


/*----------------------------------------------------
	Construct
----------------------------------------------------*/

void SFlareNotifier::Construct(const FArguments& InArgs)
{
	// Data
	MenuManager = InArgs._MenuManager;

	// Create the layout
	ChildSlot
	.VAlign(VAlign_Top)
	.HAlign(HAlign_Right)
	[
		SNew(SBox)
		.HeightOverride(900)
		.VAlign(VAlign_Bottom)
		[
			SAssignNew(NotificationContainer, SVerticalBox)
		]
	];
}


/*----------------------------------------------------
	Interaction
----------------------------------------------------*/

void SFlareNotifier::Notify(FText Text, FText Info, FName Tag, EFlareNotification::Type Type, float Timeout, EFlareMenu::Type TargetMenu, void* TargetInfo)
{
	// Remove notification with the same tag.

	if(Tag != NAME_None)
	{
		for(int Index = 0; Index < NotificationData.Num(); Index++)
		{
			if(NotificationData[Index]->IsDuplicate(Tag))
			{
				FLOG("SFlareNotifier::Notify : deleting previous because it's duplicate");
				NotificationData[Index]->Finish(false);
			}
		}
	}

	// Add notification
	TSharedPtr<SFlareNotification> NotificationEntry;
	NotificationContainer->InsertSlot(0)
	.AutoHeight()
	[
		SAssignNew(NotificationEntry, SFlareNotification)
		.MenuManager(MenuManager.Get())
		.Notifier(this)
		.Text(Text)
		.Info(Info)
		.Type(Type)
		.Tag(Tag)
		.Timeout(Timeout)
		.TargetMenu(TargetMenu)
		.TargetInfo(TargetInfo)
	];

	// Store a reference to it
	NotificationData.Add(NotificationEntry);
}

void SFlareNotifier::FlushNotifications()
{
	for (auto& NotificationEntry : NotificationData)
	{
		NotificationEntry->Finish();
	}
}


/*----------------------------------------------------
	Callbacks
----------------------------------------------------*/

void SFlareNotifier::Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime)
{
	SCompoundWidget::Tick(AllottedGeometry, InCurrentTime, InDeltaTime);
	int32 NotificationCount = 0;

	// Destroy notifications when they're done with the animation
	for (auto& NotificationEntry : NotificationData)
	{
		if (NotificationEntry->IsFinished())
		{
			NotificationContainer->RemoveSlot(NotificationEntry.ToSharedRef());
		}
		else
		{
			NotificationCount++;
		}
	}

	// Clean up the list when no notification is active
	if (NotificationCount == 0)
	{
		NotificationData.Empty();
	}
}

/*----------------------------------------------------
	Getters
----------------------------------------------------*/

bool SFlareNotifier::IsFirstNotification(SFlareNotification* Notification)
{
	for(int i = 0; i < NotificationData.Num(); i++)
	{
		if(!NotificationData[i]->IsFinished())
		{
			return NotificationData[i].Get() == Notification;
		}
	}
	return false;
}

#undef LOCTEXT_NAMESPACE
