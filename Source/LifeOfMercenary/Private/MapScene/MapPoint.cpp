// Fill out your copyright notice in the Description page of Project Settings.

#include "MapPoint.h"


// Sets default values
AMapPoint::AMapPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


void AMapPoint::PostInitProperties()
{
	Super::PostInitProperties();

}

void AMapPoint::OnConstruction(const FTransform& _transform)
{
	Super::OnConstruction(_transform);

#if WITH_EDITOR
	//���� ���� ��, ����� Spline�� �� ��ġ�� ���� �Ѱ����.
	for (int i = 0; i < splineArray.Num(); i++) {
		if (splineArray[i] != nullptr) {
			if ((GetActorLocation() - splineArray[i]->routeSpline->GetLocationAtDistanceAlongSpline(0.0f, ESplineCoordinateSpace::World)).Size() >
				(GetActorLocation() - splineArray[i]->routeSpline->GetLocationAtDistanceAlongSpline(splineArray[i]->routeSpline->GetSplineLength(), ESplineCoordinateSpace::World)).Size()) {
				splineArray[i]->routeSpline->SetLocationAtSplinePoint(splineArray[i]->routeSpline->GetNumberOfSplinePoints() - 1, GetActorLocation(), ESplineCoordinateSpace::World, true);
			}
			else {
				splineArray[i]->routeSpline->SetLocationAtSplinePoint(0, GetActorLocation(), ESplineCoordinateSpace::World, true);
			}
		}
	}


	UStaticMeshComponent* tempMesh = NewObject<UStaticMeshComponent>(this, UStaticMeshComponent::StaticClass());
	tempMesh->SetHiddenInGame(bVisibleEditorOnly);
	tempMesh->SetCastShadow(false);
	tempMesh->CreationMethod = EComponentCreationMethod::UserConstructionScript;
	tempMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	tempMesh->SetMobility(EComponentMobility::Movable);
	tempMesh->SetStaticMesh(pointMesh);
	tempMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	tempMesh->SetRelativeScale3D(tempMesh->RelativeScale3D * pointMeshRadius);
#endif
}

// Called when the game starts or when spawned
void AMapPoint::BeginPlay()
{
	Super::BeginPlay();

	SetArrayInSpline();
}

// Called every frame
void AMapPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMapPoint::SetArrayInSpline()
{
	//Spline ����
	for (int i = 0; i < splineArray.Num(); i++) {
		float dist0 = (GetActorLocation() - splineArray[i]->routeSpline->GetLocationAtDistanceAlongSpline(0.0f, ESplineCoordinateSpace::World)).Size();
		float dist1 = (GetActorLocation() - splineArray[i]->routeSpline->GetLocationAtDistanceAlongSpline(splineArray[i]->routeSpline->GetSplineLength(), ESplineCoordinateSpace::World)).Size();

		if (dist1 > dist0) {
			splineArray[i]->linkedPoint[0] = this;
		}
		else {
			splineArray[i]->linkedPoint[1] = this;
		}
	}
}
