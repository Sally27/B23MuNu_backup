// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIvolsdIlhcbdIss4314dIroofitincludecrossfeedonebinntracksdIwithmcsigreweightdIafter2bdtsdItrynewmakefiledIdocsdIcustomclassdIlibdIeventdict

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
         instance("MyCB", ::MyCB::Class_Version(), "include/MyCB.hpp", 16,
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

namespace {
  void TriggerDictionaryInitialization_eventdict_Impl() {
    static const char* headers[] = {
"MyCB.hpp",
0
    };
    static const char* includePaths[] = {
"//vols/lhcb/ss4314/roofitincludecrossfeedonebinntracks/withmcsigreweight/after2bdts/trynewmakefile/docs/customclass/include",
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
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "eventdict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "MyCB.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"MyCB", payloadCode, "@",
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
