// Fill out your copyright notice in the Description page of Project Settings.


#include "Pistol_WeaponBase.h"

APistol_WeaponBase::APistol_WeaponBase(){
    SocketName="Pistol_Socket";
    WeaponType=E_WeaponType::EWT_Pistol;

    CurrentAmmo=6;
    MaxMagAmmo=6;
    CurrentTotalAmmo=36;
    MaxTotalAmmo=36;
    ReloadTime=1.f;
    
}



void APistol_WeaponBase::WeaponFire(){
    Super::WeaponFire();
    if(FireAnimation){
        GunMesh->PlayAnimation(FireAnimation,0);
    }
    


}

void APistol_WeaponBase::WeaponReload(){
    Super::WeaponReload();

    UE_LOG(LogTemp,Warning,TEXT("ReloadingPistol"));



}



//APistol_WeaponBase
