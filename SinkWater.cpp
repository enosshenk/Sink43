

#include "Sink43.h"
#include "SinkWater.h"

#include "Engine/CanvasRenderTarget2D.h"
#include "RenderUtils.h"


ASinkWater::ASinkWater(const class FPostConstructInitializeProperties& PCIP)
: Super(PCIP), DrawingSplash(false), SplashCenter(FVector2D(512, 512)), SplashScale(0.0f), RingTexture(nullptr), ClearTexture(nullptr), MaterialInstance(nullptr)
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void ASinkWater::BeginPlay()
{
	Super::BeginPlay();

	if (CanvasTarget == nullptr)
	{
		CanvasTarget = UCanvasRenderTarget2D::CreateCanvasRenderTarget2D(UCanvasRenderTarget2D::StaticClass(), 1024, 1024);

		if (CanvasTarget != nullptr)
		{
			CanvasTarget->OnCanvasRenderTargetUpdate.AddDynamic(this, &ASinkWater::OnRecieveUpdate);
			CanvasTarget->UpdateResource();
		}
	}

	if (MaterialInstance != nullptr)
	{
		MaterialInstance->SetTextureParameterValue(FName("Texture"), CanvasTarget);
	}

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("SinkWater Received BeginPlay!"));
}

void ASinkWater::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (DrawingSplash)
	{
		SplashScale += DeltaTime / 8;

		CanvasTarget->UpdateResource();

		if (SplashScale > 1)
		{
			DrawingSplash = false;
			SplashScale = 0.0f;
		}
	}
}

void ASinkWater::MakeASplash(FVector2D Center)
{
	SplashCenter = FVector2D(Center.X + 512, Center.Y + 512);
	SplashCenter *= 1.024;
	DrawingSplash = true;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Making a splash"));
}


void ASinkWater::OnRecieveUpdate(class UCanvas* Canvas, int32 Width, int32 Height)
{
	if (Canvas != nullptr)
	{
	//	FCanvasTileItem DickButt(FVector2D(256, 256), RingTexture->Resource, FVector2D(512, 512), FVector2D(0, 0), FVector2D(1, 1), FLinearColor(1.0f, 1.0f, 1.0f));
	//	Canvas->DrawItem(DickButt);

		if (ClearTexture != nullptr)
		{
			FCanvasTileItem ClearTex(FVector2D(0, 0), ClearTexture->Resource, FVector2D(1024, 1024), FVector2D(0, 0), FVector2D(1, 1), FLinearColor(0.0f, 0.0f, 0.0f));
			Canvas->DrawItem(ClearTex);
		}

		if (DrawingSplash)
		{
			FVector2D DrawSize = FVector2D(SplashScale * 768, SplashScale * 768);
			FVector2D DrawLoc = FVector2D(SplashCenter.X - DrawSize.X / 2, SplashCenter.Y - DrawSize.Y / 2);
			
			FCanvasTileItem Ring(DrawLoc, RingTexture->Resource, DrawSize, FVector2D(0, 0), FVector2D(1, 1), FLinearColor(1 - SplashScale, 1 - SplashScale, 1 - SplashScale));
			Canvas->DrawItem(Ring);
		}
	}
}


