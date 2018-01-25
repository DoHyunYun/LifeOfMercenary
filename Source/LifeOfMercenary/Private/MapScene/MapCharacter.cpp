// Fill out your copyright notice in the Description page of Project Settings.

#include "MapCharacter.h"
#include "MapRouteSpline.h"
#include "MapPoint.h"


// Sets default values
AMapCharacter::AMapCharacter() : MovementSpeed(1000.0f)
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMapCharacter::OnConstruction(const FTransform& _transform)
{
	Super::OnConstruction(_transform);
}

// Called when the game starts or when spawned
void AMapCharacter::BeginPlay()
{
	Super::BeginPlay();

	doOnce = true;

	//적용 시 주석 풀것
	//StopMove();
}

// Called every frame
void AMapCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (doOnce) {
		StopMove();
		SetMove(targetPoint);
		doOnce = false;
		//최초 이벤트세팅
		hasSpline->SetSplineEvent();
	}

	Move();
}

// Called to bind functionality to input
void AMapCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMapCharacter::FindRoute(AMapPoint* _targetPoint) {
	SFT.Empty();

	TArray<AMapRouteSpline*> visitedSpline;
	TMap<AMapPoint*, AStarSplineFastRoute> fastRoute;

	TArray<AMapPoint*> q;

	q.Add(hasPoint);
	fastRoute.Add(hasPoint);

	AMapPoint* currentPoint = nullptr;

	while (q.Num() > 0) {
		//가장 비용이 낮은 Point POP. Cost + 목적지까지 거리
		currentPoint = q[0];

		for (int i = 0; i < q.Num(); i++) {
			/*currentPoint = (q[i]->fastCost + (q[i]->GetActorLocation() - _targetPoint->GetActorLocation()).Size()) <
			(currentPoint->fastCost + (currentPoint->GetActorLocation() - _targetPoint->GetActorLocation()).Size()) ? q[i] : currentPoint;*/
			currentPoint = (fastRoute.Find(q[i])->fastCost + (q[i]->GetActorLocation() - _targetPoint->GetActorLocation()).Size()) <
				(fastRoute.Find(currentPoint)->fastCost + (currentPoint->GetActorLocation() - _targetPoint->GetActorLocation()).Size()) ? q[i] : currentPoint;
		}
		q.RemoveAt(q.Find(currentPoint));

		//변경?
		if (currentPoint == _targetPoint)
			break;

		for (int i = 0; i < currentPoint->splineArray.Num(); i++) {
			if (visitedSpline.Find(currentPoint->splineArray[i]) != INDEX_NONE) continue;

			//Spline 반대쪽에 있는 Point
			AMapPoint* tempPoint = currentPoint->splineArray[i]->GetOtherPoint(currentPoint);

			if (!fastRoute.Contains(tempPoint))
				fastRoute.Add(tempPoint);

			if (fastRoute.Find(tempPoint)->fastSpline == nullptr) {
				fastRoute.Find(tempPoint)->fastSpline = currentPoint->splineArray[i];
				fastRoute.Find(tempPoint)->fastCost = fastRoute.Find(currentPoint)->fastCost + currentPoint->splineArray[i]->cost;

				if (!fastRoute.Contains(tempPoint))
					fastRoute.Add(tempPoint);
				q.Push(tempPoint);

				visitedSpline.Push(currentPoint->splineArray[i]);
			}
			else if (fastRoute.Find(tempPoint)->fastCost > fastRoute.Find(currentPoint)->fastCost + currentPoint->splineArray[i]->cost) {
				fastRoute.Find(tempPoint)->fastSpline = currentPoint->splineArray[i];
				fastRoute.Find(tempPoint)->fastCost = fastRoute.Find(currentPoint)->fastCost + currentPoint->splineArray[i]->cost;

				visitedSpline.Push(currentPoint->splineArray[i]);
			}
		}

		//길을 못찾았으면,
		if (q.Num() <= 0) return;
	}

	while (currentPoint != hasPoint)
	{
		SFT.Push(fastRoute.Find(currentPoint)->fastSpline);
		currentPoint = fastRoute.Find(currentPoint)->fastSpline->GetOtherPoint(currentPoint);
	}
}

bool AMapCharacter::SetMove(AMapPoint* _targetPoint)
{
	if (_targetPoint == nullptr) return false;

	//이동중이 아니고, 저장된 최단거리 기록이 없을경우.
	if (StartMove() && SFT.Num() <= 0) {
		targetPoint = _targetPoint;
		FindRoute(_targetPoint);
		AMapRouteSpline* tempSpline = SFT.Pop();
		hasSpline = tempSpline;
		if (hasSpline->PointStartDirectionBoolean(hasPoint))
			distanceAlongSpline = 0.0f;
		else
			distanceAlongSpline = 1.0f;
		return true;
	}
	else {
		return false;
	}
}

void AMapCharacter::StopMove()
{
	SetActorTickEnabled(false);//InActive Tick
}

bool AMapCharacter::StartMove()
{
	if (!IsActorTickEnabled()) {
		SetActorTickEnabled(true);//Active Tick
		return true;
	}
	else {
		return false;
	}
}

void AMapCharacter::Move()
{
	//다음 이동포인트 좌표
	const FVector destination = hasSpline->routeSpline->GetLocationAtDistanceAlongSpline(distanceAlongSpline * hasSpline->routeSpline->GetSplineLength(), ESplineCoordinateSpace::World);

	TArray<AActor*> tempActorArray;
	TArray<FHitResult> landScape;
	UKismetSystemLibrary::LineTraceMulti(GetWorld(),
		FVector(destination.X, destination.Y, GetActorLocation().Z + 1000.0f),
		FVector(destination.X, destination.Y, GetActorLocation().Z - 1000.0f),
		ETraceTypeQuery::TraceTypeQuery1,
		false, tempActorArray, EDrawDebugTrace::None, landScape, true);

	//===================== 이동 ==========================
	//Spline의 해당(비율) 위치 좌표 불러옴.
	FVector movePos = destination;
	//목적지의 XY위치와 캐릭터 Z위치 합성 및 방향벡터 확인.
	movePos = (FVector(movePos.X, movePos.Y, landScape[0].Location.Z) - GetActorLocation());
	movePos = movePos / movePos.Size();

	AddMovementInput(movePos, MovementSpeed / 1000.0f);
	//=====================================================

	//===================== 이벤트 발생 ===========================
	if (hasSpline->GetEventNumber() > 0)
		hasSpline->EventCall(distanceAlongSpline, hasSpline->PointStartDirectionBoolean(hasPoint));
	//=============================================================

	//다음위치 얻어오기. distanceAlongSpline에 비율(0~1.0f)로 기록
	//다음 이동포인트까지 도착했는지 확인.
	if ((destination - FVector(GetActorLocation().X, GetActorLocation().Y, destination.Z)).Size() < 100.0f) {
		//중간 목적지에 도착했다면
		if (distanceAlongSpline < 0.0f || distanceAlongSpline > 1.0f) {
			//최종목적지가 아니라면
			if (SFT.Num() > 0) {
				//도착한 곳을 현재위치로
				hasPoint = hasSpline->GetOtherPoint(hasPoint);
				//최단거리 배열에서 다음 Spline을 얻어옴.
				hasSpline = SFT.Pop();
				//시작지점이 정방향인지 역방향인지 확인하여 세팅(0.0f 정방향, 1.0f 역방향)
				if (hasSpline->PointStartDirectionBoolean(hasPoint)) {
					distanceAlongSpline = 0.0f;
				}
				else {
					distanceAlongSpline = 1.0f;
				}

				//이벤트 세팅
				hasSpline->SetSplineEvent();
			}
			//최종목적지라면
			else {
				//도착한 곳을 현재위치로
				hasPoint = hasSpline->GetOtherPoint(hasPoint);
				//이동 종료.
				StopMove();
			}
		}
		//아직 진행중이라면,
		else {
			//다음 지점 받아옴. PointStartLengthZero()는 정방향인지 역방향인지 양음수 역할.
			distanceAlongSpline += GetWorld()->DeltaTimeSeconds * MovementSpeed * hasSpline->PointStartDirection(hasPoint) / hasSpline->routeSpline->GetSplineLength();
			//비율 = 경과시간 * (속도 / 총 길이)
		}
	}
}
