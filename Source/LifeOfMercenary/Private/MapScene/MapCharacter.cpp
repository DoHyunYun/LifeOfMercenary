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

	//���� �� �ּ� Ǯ��
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
		//���� �̺�Ʈ����
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
		//���� ����� ���� Point POP. Cost + ���������� �Ÿ�
		currentPoint = q[0];

		for (int i = 0; i < q.Num(); i++) {
			/*currentPoint = (q[i]->fastCost + (q[i]->GetActorLocation() - _targetPoint->GetActorLocation()).Size()) <
			(currentPoint->fastCost + (currentPoint->GetActorLocation() - _targetPoint->GetActorLocation()).Size()) ? q[i] : currentPoint;*/
			currentPoint = (fastRoute.Find(q[i])->fastCost + (q[i]->GetActorLocation() - _targetPoint->GetActorLocation()).Size()) <
				(fastRoute.Find(currentPoint)->fastCost + (currentPoint->GetActorLocation() - _targetPoint->GetActorLocation()).Size()) ? q[i] : currentPoint;
		}
		q.RemoveAt(q.Find(currentPoint));

		//����?
		if (currentPoint == _targetPoint)
			break;

		for (int i = 0; i < currentPoint->splineArray.Num(); i++) {
			if (visitedSpline.Find(currentPoint->splineArray[i]) != INDEX_NONE) continue;

			//Spline �ݴ��ʿ� �ִ� Point
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

		//���� ��ã������,
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

	//�̵����� �ƴϰ�, ����� �ִܰŸ� ����� �������.
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
	//���� �̵�����Ʈ ��ǥ
	const FVector destination = hasSpline->routeSpline->GetLocationAtDistanceAlongSpline(distanceAlongSpline * hasSpline->routeSpline->GetSplineLength(), ESplineCoordinateSpace::World);

	TArray<AActor*> tempActorArray;
	TArray<FHitResult> landScape;
	UKismetSystemLibrary::LineTraceMulti(GetWorld(),
		FVector(destination.X, destination.Y, GetActorLocation().Z + 1000.0f),
		FVector(destination.X, destination.Y, GetActorLocation().Z - 1000.0f),
		ETraceTypeQuery::TraceTypeQuery1,
		false, tempActorArray, EDrawDebugTrace::None, landScape, true);

	//===================== �̵� ==========================
	//Spline�� �ش�(����) ��ġ ��ǥ �ҷ���.
	FVector movePos = destination;
	//�������� XY��ġ�� ĳ���� Z��ġ �ռ� �� ���⺤�� Ȯ��.
	movePos = (FVector(movePos.X, movePos.Y, landScape[0].Location.Z) - GetActorLocation());
	movePos = movePos / movePos.Size();

	AddMovementInput(movePos, MovementSpeed / 1000.0f);
	//=====================================================

	//===================== �̺�Ʈ �߻� ===========================
	if (hasSpline->GetEventNumber() > 0)
		hasSpline->EventCall(distanceAlongSpline, hasSpline->PointStartDirectionBoolean(hasPoint));
	//=============================================================

	//������ġ ������. distanceAlongSpline�� ����(0~1.0f)�� ���
	//���� �̵�����Ʈ���� �����ߴ��� Ȯ��.
	if ((destination - FVector(GetActorLocation().X, GetActorLocation().Y, destination.Z)).Size() < 100.0f) {
		//�߰� �������� �����ߴٸ�
		if (distanceAlongSpline < 0.0f || distanceAlongSpline > 1.0f) {
			//������������ �ƴ϶��
			if (SFT.Num() > 0) {
				//������ ���� ������ġ��
				hasPoint = hasSpline->GetOtherPoint(hasPoint);
				//�ִܰŸ� �迭���� ���� Spline�� ����.
				hasSpline = SFT.Pop();
				//���������� ���������� ���������� Ȯ���Ͽ� ����(0.0f ������, 1.0f ������)
				if (hasSpline->PointStartDirectionBoolean(hasPoint)) {
					distanceAlongSpline = 0.0f;
				}
				else {
					distanceAlongSpline = 1.0f;
				}

				//�̺�Ʈ ����
				hasSpline->SetSplineEvent();
			}
			//�������������
			else {
				//������ ���� ������ġ��
				hasPoint = hasSpline->GetOtherPoint(hasPoint);
				//�̵� ����.
				StopMove();
			}
		}
		//���� �������̶��,
		else {
			//���� ���� �޾ƿ�. PointStartLengthZero()�� ���������� ���������� ������ ����.
			distanceAlongSpline += GetWorld()->DeltaTimeSeconds * MovementSpeed * hasSpline->PointStartDirection(hasPoint) / hasSpline->routeSpline->GetSplineLength();
			//���� = ����ð� * (�ӵ� / �� ����)
		}
	}
}
