// Fill out your copyright notice in the Description page of Project Settings.

#include "AttackStartNotifyState.h"
#include "PunchKick01Character.h"

void UAttackStartNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                          float TotalDuration)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, __FUNCTION__);

	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		APunchKick01Character* Player = Cast<APunchKick01Character>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->AttackStart();
		}
	}
}

void UAttackStartNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	GEngine->AddOnScreenDebugMessage(-1, 4.5f, FColor::Magenta, __FUNCTION__);

	Super::NotifyEnd(MeshComp, Animation);

	if (MeshComp != nullptr && MeshComp->GetOwner() != nullptr)
	{
		APunchKick01Character* Player = Cast<APunchKick01Character>(MeshComp->GetOwner());

		if (Player != nullptr)
		{
			Player->AttackEnd();
		}
	}
}
