#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class SlateLibraryEditor : public FDefaultModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	const static FName DockableTabId;

private:
	void ExtendTopBarMenu(FMenuBarBuilder& Builder);
	void MakeTrainingMenu(FMenuBuilder& MenuBuilder);

	void OpenSlateTableWidget();
	
	// Dockable tab spawner
	TSharedRef<SDockTab> SpawnDockableTab(const FSpawnTabArgs& Args);
};
