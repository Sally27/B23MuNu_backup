// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIvolsdIlhcbdIss4314dIcustomlibdIlibdIeventdict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "MyCB.hpp"
#include "RooHypathia.hpp"
#include "RooIpatia2.hpp"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_MyCB(void *p = 0);
   static void *newArray_MyCB(Long_t size, void *p);
   static void delete_MyCB(void *p);
   static void deleteArray_MyCB(void *p);
   static void destruct_MyCB(void *p);
   static void streamer_MyCB(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::MyCB*)
   {
      ::MyCB *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::MyCB >(0);
      static ::ROOT::TGenericClassInfo 
         instance("MyCB", ::MyCB::Class_Version(), "MyCB.hpp", 16,
                  typeid(::MyCB), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::MyCB::Dictionary, isa_proxy, 16,
                  sizeof(::MyCB) );
      instance.SetNew(&new_MyCB);
      instance.SetNewArray(&newArray_MyCB);
      instance.SetDelete(&delete_MyCB);
      instance.SetDeleteArray(&deleteArray_MyCB);
      instance.SetDestructor(&destruct_MyCB);
      instance.SetStreamerFunc(&streamer_MyCB);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::MyCB*)
   {
      return GenerateInitInstanceLocal((::MyCB*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::MyCB*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooHypathia(void *p = 0);
   static void *newArray_RooHypathia(Long_t size, void *p);
   static void delete_RooHypathia(void *p);
   static void deleteArray_RooHypathia(void *p);
   static void destruct_RooHypathia(void *p);
   static void streamer_RooHypathia(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooHypathia*)
   {
      ::RooHypathia *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooHypathia >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooHypathia", ::RooHypathia::Class_Version(), "RooHypathia.hpp", 8,
                  typeid(::RooHypathia), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooHypathia::Dictionary, isa_proxy, 16,
                  sizeof(::RooHypathia) );
      instance.SetNew(&new_RooHypathia);
      instance.SetNewArray(&newArray_RooHypathia);
      instance.SetDelete(&delete_RooHypathia);
      instance.SetDeleteArray(&deleteArray_RooHypathia);
      instance.SetDestructor(&destruct_RooHypathia);
      instance.SetStreamerFunc(&streamer_RooHypathia);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooHypathia*)
   {
      return GenerateInitInstanceLocal((::RooHypathia*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooHypathia*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RooIpatia2(void *p = 0);
   static void *newArray_RooIpatia2(Long_t size, void *p);
   static void delete_RooIpatia2(void *p);
   static void deleteArray_RooIpatia2(void *p);
   static void destruct_RooIpatia2(void *p);
   static void streamer_RooIpatia2(TBuffer &buf, void *obj);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RooIpatia2*)
   {
      ::RooIpatia2 *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RooIpatia2 >(0);
      static ::ROOT::TGenericClassInfo 
         instance("RooIpatia2", ::RooIpatia2::Class_Version(), "RooIpatia2.hpp", 10,
                  typeid(::RooIpatia2), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RooIpatia2::Dictionary, isa_proxy, 16,
                  sizeof(::RooIpatia2) );
      instance.SetNew(&new_RooIpatia2);
      instance.SetNewArray(&newArray_RooIpatia2);
      instance.SetDelete(&delete_RooIpatia2);
      instance.SetDeleteArray(&deleteArray_RooIpatia2);
      instance.SetDestructor(&destruct_RooIpatia2);
      instance.SetStreamerFunc(&streamer_RooIpatia2);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RooIpatia2*)
   {
      return GenerateInitInstanceLocal((::RooIpatia2*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_(Init) = GenerateInitInstanceLocal((const ::RooIpatia2*)0x0); R__UseDummy(_R__UNIQUE_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr MyCB::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *MyCB::Class_Name()
{
   return "MyCB";
}

//______________________________________________________________________________
const char *MyCB::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyCB*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int MyCB::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::MyCB*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *MyCB::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyCB*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *MyCB::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::MyCB*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooHypathia::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RooHypathia::Class_Name()
{
   return "RooHypathia";
}

//______________________________________________________________________________
const char *RooHypathia::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooHypathia*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RooHypathia::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooHypathia*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooHypathia::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooHypathia*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooHypathia::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooHypathia*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RooIpatia2::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *RooIpatia2::Class_Name()
{
   return "RooIpatia2";
}

//______________________________________________________________________________
const char *RooIpatia2::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooIpatia2*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int RooIpatia2::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RooIpatia2*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RooIpatia2::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooIpatia2*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RooIpatia2::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD2(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RooIpatia2*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void MyCB::Streamer(TBuffer &R__b)
{
   // Stream an object of class MyCB.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      mean.Streamer(R__b);
      sigma.Streamer(R__b);
      al.Streamer(R__b);
      nl.Streamer(R__b);
      ar.Streamer(R__b);
      nr.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, MyCB::IsA());
   } else {
      R__c = R__b.WriteVersion(MyCB::IsA(), kTRUE);
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      mean.Streamer(R__b);
      sigma.Streamer(R__b);
      al.Streamer(R__b);
      nl.Streamer(R__b);
      ar.Streamer(R__b);
      nr.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_MyCB(void *p) {
      return  p ? new(p) ::MyCB : new ::MyCB;
   }
   static void *newArray_MyCB(Long_t nElements, void *p) {
      return p ? new(p) ::MyCB[nElements] : new ::MyCB[nElements];
   }
   // Wrapper around operator delete
   static void delete_MyCB(void *p) {
      delete ((::MyCB*)p);
   }
   static void deleteArray_MyCB(void *p) {
      delete [] ((::MyCB*)p);
   }
   static void destruct_MyCB(void *p) {
      typedef ::MyCB current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_MyCB(TBuffer &buf, void *obj) {
      ((::MyCB*)obj)->::MyCB::Streamer(buf);
   }
} // end of namespace ROOT for class ::MyCB

//______________________________________________________________________________
void RooHypathia::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooHypathia.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      RooAbsPdf::Streamer(R__b);
      mass_.Streamer(R__b);
      mean_.Streamer(R__b);
      sigma_.Streamer(R__b);
      lambda_.Streamer(R__b);
      zeta_.Streamer(R__b);
      beta_.Streamer(R__b);
      a_.Streamer(R__b);
      n_.Streamer(R__b);
      R__b >> uselog_;
      R__b.CheckByteCount(R__s, R__c, RooHypathia::IsA());
   } else {
      R__c = R__b.WriteVersion(RooHypathia::IsA(), kTRUE);
      RooAbsPdf::Streamer(R__b);
      mass_.Streamer(R__b);
      mean_.Streamer(R__b);
      sigma_.Streamer(R__b);
      lambda_.Streamer(R__b);
      zeta_.Streamer(R__b);
      beta_.Streamer(R__b);
      a_.Streamer(R__b);
      n_.Streamer(R__b);
      R__b << uselog_;
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooHypathia(void *p) {
      return  p ? new(p) ::RooHypathia : new ::RooHypathia;
   }
   static void *newArray_RooHypathia(Long_t nElements, void *p) {
      return p ? new(p) ::RooHypathia[nElements] : new ::RooHypathia[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooHypathia(void *p) {
      delete ((::RooHypathia*)p);
   }
   static void deleteArray_RooHypathia(void *p) {
      delete [] ((::RooHypathia*)p);
   }
   static void destruct_RooHypathia(void *p) {
      typedef ::RooHypathia current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RooHypathia(TBuffer &buf, void *obj) {
      ((::RooHypathia*)obj)->::RooHypathia::Streamer(buf);
   }
} // end of namespace ROOT for class ::RooHypathia

//______________________________________________________________________________
void RooIpatia2::Streamer(TBuffer &R__b)
{
   // Stream an object of class RooIpatia2.

   UInt_t R__s, R__c;
   if (R__b.IsReading()) {
      Version_t R__v = R__b.ReadVersion(&R__s, &R__c); if (R__v) { }
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      l.Streamer(R__b);
      zeta.Streamer(R__b);
      fb.Streamer(R__b);
      sigma.Streamer(R__b);
      mu.Streamer(R__b);
      a.Streamer(R__b);
      n.Streamer(R__b);
      a2.Streamer(R__b);
      n2.Streamer(R__b);
      R__b.CheckByteCount(R__s, R__c, RooIpatia2::IsA());
   } else {
      R__c = R__b.WriteVersion(RooIpatia2::IsA(), kTRUE);
      RooAbsPdf::Streamer(R__b);
      x.Streamer(R__b);
      l.Streamer(R__b);
      zeta.Streamer(R__b);
      fb.Streamer(R__b);
      sigma.Streamer(R__b);
      mu.Streamer(R__b);
      a.Streamer(R__b);
      n.Streamer(R__b);
      a2.Streamer(R__b);
      n2.Streamer(R__b);
      R__b.SetByteCount(R__c, kTRUE);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RooIpatia2(void *p) {
      return  p ? new(p) ::RooIpatia2 : new ::RooIpatia2;
   }
   static void *newArray_RooIpatia2(Long_t nElements, void *p) {
      return p ? new(p) ::RooIpatia2[nElements] : new ::RooIpatia2[nElements];
   }
   // Wrapper around operator delete
   static void delete_RooIpatia2(void *p) {
      delete ((::RooIpatia2*)p);
   }
   static void deleteArray_RooIpatia2(void *p) {
      delete [] ((::RooIpatia2*)p);
   }
   static void destruct_RooIpatia2(void *p) {
      typedef ::RooIpatia2 current_t;
      ((current_t*)p)->~current_t();
   }
   // Wrapper around a custom streamer member function.
   static void streamer_RooIpatia2(TBuffer &buf, void *obj) {
      ((::RooIpatia2*)obj)->::RooIpatia2::Streamer(buf);
   }
} // end of namespace ROOT for class ::RooIpatia2

namespace {
  void TriggerDictionaryInitialization_eventdict_Impl() {
    static const char* headers[] = {
"MyCB.hpp",
"RooHypathia.hpp",
"RooIpatia2.hpp",
0
    };
    static const char* includePaths[] = {
"//vols/lhcb/ss4314/customlib/include",
"/cvmfs/lhcb.cern.ch/lib/lcg/releases/ROOT/6.06.02-6cc9c/x86_64-slc6-gcc49-opt/include",
"/vols/lhcb/ss4314/customlib/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "eventdict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(Your description goes here...)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$MyCB.hpp")))  MyCB;
class __attribute__((annotate("$clingAutoload$RooHypathia.hpp")))  RooHypathia;
class __attribute__((annotate(R"ATTRDUMP(Your description goes here...)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$RooIpatia2.hpp")))  RooIpatia2;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "eventdict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "MyCB.hpp"
#include "RooHypathia.hpp"
#include "RooIpatia2.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"MyCB", payloadCode, "@",
"RooHypathia", payloadCode, "@",
"RooIpatia2", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("eventdict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_eventdict_Impl, {}, classesHeaders);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_eventdict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_eventdict() {
  TriggerDictionaryInitialization_eventdict_Impl();
}
