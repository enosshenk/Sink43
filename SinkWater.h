

#pragma once

#include "GameFramework/Actor.h"
#include "RenderCore.h"
#include "RenderUtils.h"
#include "SinkWater.generated.h"

/**
 * 
 */
UCLASS()
class SINK43_API ASinkWater : public AActor
{
	GENERATED_UCLASS_BODY()

public:
	UFUNCTION()
	virtual void OnRecieveUpdate(class UCanvas* Canvas, int32 Width, int32 Height);

	UFUNCTION()
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category=Sink)
	virtual void MakeASplash(FVector2D Center);

	UPROPERTY(BlueprintReadWrite, Category = Target)
	class UTexture2D* RingTexture;

	UPROPERTY(BlueprintReadWrite, Category = Target)
	class UTexture2D* ClearTexture;

	UPROPERTY(BlueprintReadWrite, Category = Target)
	class UMaterialInstanceDynamic* MaterialInstance;

private:
	bool DrawingSplash;

	FVector2D SplashCenter;

	float SplashScale;

protected:
	UPROPERTY()
	class UCanvasRenderTarget2D* CanvasTarget;
};
