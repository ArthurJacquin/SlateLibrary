#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleInterface.h"

class SlateLibraryEditorModule : public FDefaultModuleImpl
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	void ExtendTopBarMenu(FMenuBarBuilder& Builder);
	void MakeTrainingMenu(FMenuBuilder& MenuBuilder);

	void OpenSlateTableWidget();
};
