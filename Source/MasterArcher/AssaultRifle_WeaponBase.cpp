// Fill out your copyright notice in the Description page of Project Settings.


#include "AssaultRifle_WeaponBase.h"

AAssaultRifle_WeaponBase::AAssaultRifle_WeaponBase(){
    SocketName="AssaultRifle_Socket";
    WeaponType=E_WeaponType::EWT_AssaultRifle;

    CurrentAmmo=10;
    MaxMagAmmo=10;
    CurrentTotalAmmo=180;
    MaxTotalAmmo=180;
    ReloadTime=1.f;

}

void AAssaultRifle_WeaponBase::WeaponFire(){
    Super::WeaponFire();
    if(FireAnimMontage){
        bFiring=1;
        UAnimInstance* AnimInstance = GunMesh->GetAnimInstance();
        if(AnimInstance&&FireAnimMontage){
            AnimInstance->Montage_Play(FireAnimMontage, 1.f);
            AnimInstance->Montage_JumpToSection(TEXT("Default"));
        
            //GunMesh->PlayAnimation(FireAnimation,0);
            GetWorldTimerManager().SetTimer(TH_FireAnim,this,&AAssaultRifle_WeaponBase::EndFireAnim,.1f);
        }
    }
    


}

void AAssaultRifle_WeaponBase::WeaponReload(){
    Super::WeaponReload();
    if(ReloadAnimation){
        //GunMesh->PlayAnimation(ReloadAnimation,0);
    }
    UE_LOG(LogTemp,Warning,TEXT("ReloadingAR"));



}

void AAssaultRifle_WeaponBase::EndFireAnim(){
    bFiring=0;
    GetWorldTimerManager().ClearTimer(TH_FireAnim);

}