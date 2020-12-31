//#pragma once
//#include "FeatureLearning.h"
//#include "Shader.h"
//class FShaderParameterMapInfo_Ge
//{
//	DECLARE_TYPE_LAYOUT(FShaderParameterMapInfo_Ge, NonVirtual);
//public:
//	LAYOUT_FIELD(TMemoryImageArray<FShaderParameterInfo>, UniformBuffers);
//	LAYOUT_FIELD(TMemoryImageArray<FShaderParameterInfo>, TextureSamplers);
//	LAYOUT_FIELD(TMemoryImageArray<FShaderParameterInfo>, SRVs);
//	LAYOUT_FIELD(TMemoryImageArray<FShaderLooseParameterBufferInfo>, LooseParameterBuffers);
//
//	friend FArchive& operator<<(FArchive& Ar, FShaderParameterMapInfo_Ge& Info)
//	{
//		Ar << Info.UniformBuffers;
//		Ar << Info.TextureSamplers;
//		Ar << Info.SRVs;
//		Ar << Info.LooseParameterBuffers;
//		return Ar;
//	}
//
//	inline bool operator==(const FShaderParameterMapInfo_Ge& Rhs) const
//	{
//		return UniformBuffers == Rhs.UniformBuffers
//			&& TextureSamplers == Rhs.TextureSamplers
//			&& SRVs == Rhs.SRVs
//			&& LooseParameterBuffers == Rhs.LooseParameterBuffers;
//	}
//};
//
//
//class FShaderParameterMapInfo_Ge {
//private:
//	using InternalBaseType = typename TGetBaseTypeHelper< FShaderParameterMapInfo_Ge>::Type;
//	template<typename InternalType>
//	static void InternalInitializeBases(FTypeLayoutDesc& TypeDesc) {
//		TInitializeBaseHelper<InternalType, InternalBaseType>::Initialize(TypeDesc);
//	};
//public:
//	static FTypeLayoutDesc& StaticGetTypeLayout();
//public:
//	const FTypeLayoutDesc& GetTypeLayout() const;
//	static const int CounterBase = 166;
//public:
//	using DerivedType = FShaderParameterMapInfo_Ge;
//	static const ETypeLayoutInterface::Type InterfaceType = ETypeLayoutInterface::NonVirtual;
//	template<int Counter>
//	struct InternalLinkType {
//		static __forceinline void Initialize(FTypeLayoutDesc& TypeDesc) {}
//	};
//public:
//	TMemoryImageArray<FShaderParameterInfo> UniformBuffers;
//	__pragma(warning(push)) __pragma(warning(disable: 4995)) __pragma(warning(disable: 4996))
//		template<>
//	struct InternalLinkType<167 - CounterBase> {
//		;
//		static void Initialize(FTypeLayoutDesc& TypeDesc) {
//			InternalLinkType<167 - CounterBase + 1>::Initialize(TypeDesc);
//			alignas(FFieldLayoutDesc) static uint8 FieldBuffer[sizeof(FFieldLayoutDesc)] = { 0 };
//			FFieldLayoutDesc& FieldDesc = *(FFieldLayoutDesc*)FieldBuffer;
//			FieldDesc.Name = L"UniformBuffers";
//			FieldDesc.UFieldNameLength = Freeze::FindFieldNameLength(FieldDesc.Name);
//			FieldDesc.Type = &StaticGetTypeLayoutDesc< TMemoryImageArray<FShaderParameterInfo>>();
//			FieldDesc.WriteFrozenMemoryImageFunc = TGetFreezeImageFieldHelper< TMemoryImageArray<FShaderParameterInfo>>::Do();
//			FieldDesc.Offset = __builtin_offsetof(DerivedType, UniformBuffers);
//			FieldDesc.NumArray = 1u;
//			FieldDesc.Flags = EFieldLayoutFlags::MakeFlags();
//			FieldDesc.BitFieldSize = 0u;
//			FieldDesc.Next = TypeDesc.Fields;
//			TypeDesc.Fields = &FieldDesc;
//		}
//	}
//	;
//	__pragma(warning(pop));
//	TMemoryImageArray<FShaderParameterInfo> TextureSamplers;
//	__pragma(warning(push)) __pragma(warning(disable: 4995)) __pragma(warning(disable: 4996)) template<> struct InternalLinkType<168 - CounterBase> {
//		;
//		static void Initialize(FTypeLayoutDesc& TypeDesc) {
//			InternalLinkType<168 - CounterBase + 1>::Initialize(TypeDesc);
//			alignas(FFieldLayoutDesc) static uint8 FieldBuffer[sizeof(FFieldLayoutDesc)] = {
//				0
//			}
//			;
//			FFieldLayoutDesc& FieldDesc = *(FFieldLayoutDesc*)FieldBuffer;
//			FieldDesc.Name = L"TextureSamplers";
//			FieldDesc.UFieldNameLength = Freeze::FindFieldNameLength(FieldDesc.Name);
//			FieldDesc.Type = &StaticGetTypeLayoutDesc< TMemoryImageArray<FShaderParameterInfo>>();
//			FieldDesc.WriteFrozenMemoryImageFunc = TGetFreezeImageFieldHelper< TMemoryImageArray<FShaderParameterInfo>>::Do();
//			FieldDesc.Offset = __builtin_offsetof(DerivedType, TextureSamplers);
//			FieldDesc.NumArray = 1u;
//			FieldDesc.Flags = EFieldLayoutFlags::MakeFlags();
//			FieldDesc.BitFieldSize = 0u;
//			FieldDesc.Next = TypeDesc.Fields;
//			TypeDesc.Fields = &FieldDesc;
//		}
//	}
//	;
//	__pragma(warning(pop));
//	TMemoryImageArray<FShaderParameterInfo> SRVs;
//	__pragma(warning(push)) __pragma(warning(disable: 4995)) __pragma(warning(disable: 4996)) template<> struct InternalLinkType<169 - CounterBase> {
//		;
//		static void Initialize(FTypeLayoutDesc& TypeDesc) {
//			InternalLinkType<169 - CounterBase + 1>::Initialize(TypeDesc);
//			alignas(FFieldLayoutDesc) static uint8 FieldBuffer[sizeof(FFieldLayoutDesc)] = {
//				0
//			}
//			;
//			FFieldLayoutDesc& FieldDesc = *(FFieldLayoutDesc*)FieldBuffer;
//			FieldDesc.Name = L"SRVs";
//			FieldDesc.UFieldNameLength = Freeze::FindFieldNameLength(FieldDesc.Name);
//			FieldDesc.Type = &StaticGetTypeLayoutDesc< TMemoryImageArray<FShaderParameterInfo>>();
//			FieldDesc.WriteFrozenMemoryImageFunc = TGetFreezeImageFieldHelper< TMemoryImageArray<FShaderParameterInfo>>::Do();
//			FieldDesc.Offset = __builtin_offsetof(DerivedType, SRVs);
//			FieldDesc.NumArray = 1u;
//			FieldDesc.Flags = EFieldLayoutFlags::MakeFlags();
//			FieldDesc.BitFieldSize = 0u;
//			FieldDesc.Next = TypeDesc.Fields;
//			TypeDesc.Fields = &FieldDesc;
//		}
//	}
//	;
//	__pragma(warning(pop));
//	TMemoryImageArray<FShaderLooseParameterBufferInfo> LooseParameterBuffers;
//	__pragma(warning(push)) __pragma(warning(disable: 4995)) __pragma(warning(disable: 4996)) template<> struct InternalLinkType<170 - CounterBase> {
//		;
//		static void Initialize(FTypeLayoutDesc& TypeDesc) {
//			InternalLinkType<170 - CounterBase + 1>::Initialize(TypeDesc);
//			alignas(FFieldLayoutDesc) static uint8 FieldBuffer[sizeof(FFieldLayoutDesc)] = {
//				0
//			}
//			;
//			FFieldLayoutDesc& FieldDesc = *(FFieldLayoutDesc*)FieldBuffer;
//			FieldDesc.Name = L"LooseParameterBuffers";
//			FieldDesc.UFieldNameLength = Freeze::FindFieldNameLength(FieldDesc.Name);
//			FieldDesc.Type = &StaticGetTypeLayoutDesc< TMemoryImageArray<FShaderLooseParameterBufferInfo>>();
//			FieldDesc.WriteFrozenMemoryImageFunc = TGetFreezeImageFieldHelper< TMemoryImageArray<FShaderLooseParameterBufferInfo>>::Do();
//			FieldDesc.Offset = __builtin_offsetof(DerivedType, LooseParameterBuffers);
//			FieldDesc.NumArray = 1u;
//			FieldDesc.Flags = EFieldLayoutFlags::MakeFlags();
//			FieldDesc.BitFieldSize = 0u;
//			FieldDesc.Next = TypeDesc.Fields;
//			TypeDesc.Fields = &FieldDesc;
//		}
//	}
//	;
//	__pragma(warning(pop));
//	friend FArchive& operator<<(FArchive& Ar, FShaderParameterMapInfo_Ge& Info) {
//		Ar << Info.UniformBuffers;
//		Ar << Info.TextureSamplers;
//		Ar << Info.SRVs;
//		Ar << Info.LooseParameterBuffers;
//		return Ar;
//	}
//	inline bool operator==(const FShaderParameterMapInfo_Ge& Rhs) const {
//		return UniformBuffers == Rhs.UniformBuffers
//			&& TextureSamplers == Rhs.TextureSamplers
//			&& SRVs == Rhs.SRVs
//			&& LooseParameterBuffers == Rhs.LooseParameterBuffers;
//	}
//}
//;
//
//FTypeLayoutDesc& FShaderParameterMapInfo::StaticGetTypeLayout() 
//{
//	static_assert(TValidateInterfaceHelper< FShaderParameterMapInfo, InterfaceType>::Value, "Invalid interface for " "FShaderParameterMapInfo");
//	alignas(FTypeLayoutDesc) static uint8 TypeBuffer[sizeof(FTypeLayoutDesc)] = {0};
//	FTypeLayoutDesc& TypeDesc = *(FTypeLayoutDesc*)TypeBuffer;
//	if (!TypeDesc.IsInitialized) {
//		TypeDesc.IsInitialized = true;
//		TypeDesc.Name = L"FShaderParameterMapInfo";
//		TypeDesc.WriteFrozenMemoryImageFunc = TGetFreezeImageHelper< FShaderParameterMapInfo>::Do();
//		TypeDesc.UnfrozenCopyFunc = &Freeze::DefaultUnfrozenCopy;
//		TypeDesc.AppendHashFunc = &Freeze::DefaultAppendHash;
//		TypeDesc.GetTargetAlignmentFunc = &Freeze::DefaultGetTargetAlignment;
//		TypeDesc.ToStringFunc = &Freeze::DefaultToString;
//		TypeDesc.Size = sizeof(FShaderParameterMapInfo);
//		TypeDesc.Alignment = alignof(FShaderParameterMapInfo);
//		TypeDesc.Interface = InterfaceType;
//		TypeDesc.SizeFromFields = ~0u;
//		TAssignDestroyHelper< FShaderParameterMapInfo, TIsTriviallyDestructible< FShaderParameterMapInfo>::Value>::Do(TypeDesc);
//		TypeDesc.GetDefaultObjectFunc = &TGetDefaultObjectHelper< FShaderParameterMapInfo, InterfaceType>::Do;
//		InternalLinkType<1>::Initialize(TypeDesc);
//		InternalInitializeBases< FShaderParameterMapInfo>(TypeDesc);
//		FTypeLayoutDesc::Initialize(TypeDesc);
//	}
//	return TypeDesc;
//}
//;
//const FTypeLayoutDesc& FShaderParameterMapInfo::GetTypeLayout() const {
//	return StaticGetTypeLayout();
//}
//;
//static const FDelayedAutoRegisterHelper DelayedAutoRegisterHelper171(EDelayedRegisterRunPhase::ShaderTypesReady, [] {
//	FTypeLayoutDesc::Register(FShaderParameterMapInfo::StaticGetTypeLayout());
//}
//);
//;