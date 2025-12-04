#include "../Public/EditorUtilities.h"

void UEditorUtilities::RefreshEditorViewports()
{
    if (GEditor)
    {
        // Iterate over all viewport clients and invalidate their view to force redraw
        const TArray<FEditorViewportClient*>& Viewports = GEditor->GetAllViewportClients();
        for (FEditorViewportClient* ViewportClient : Viewports)
        {
            if (ViewportClient)
            {
                ViewportClient->Invalidate();
                ViewportClient->Viewport->Draw();
            }
        }
    }
}
