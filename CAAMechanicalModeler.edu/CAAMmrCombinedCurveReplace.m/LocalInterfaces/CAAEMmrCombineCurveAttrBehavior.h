// Copyright Dassault Systemes 2000
#ifndef CAAEMmrCombineCurveAttrBehavior_H
#define CAAEMmrCombineCurveAttrBehavior_H

//===========================================================================
//  Abstract of the class:
//  ----------------------
//
//  Code extension implementing the CATIAttrBehavior interface ,
//  which describes expected behavior on object valuating an attribute.
//  This extension extends the CombineCurve Feature.
//
//===========================================================================
//  Inheritance:
//  ------------
//              CATBaseUnknown (System Framework)
//
//===========================================================================
//  Main Method:
//  ------------
//
//  GetRequestedBehavior
//
//===========================================================================
// System Framework
#include "CATBaseUnknown.h"   // Base class for CAAEMmrCombineCurveAttrBehavior

// ObjectSpecsModeler Framework
#include "CATBehaviorSpecs.h" // To return the Behavior of an Attribute

// System Framework
class CATUnicodeString;       // To handle Attribute Names 

class CAAEMmrCombineCurveAttrBehavior : public CATBaseUnknown
{
 public :
   CATDeclareClass;
  
   CAAEMmrCombineCurveAttrBehavior();
   virtual ~CAAEMmrCombineCurveAttrBehavior();

   /**
     * Returns for a given attribute the expected behavior of its valuating objects
     * @param ipAttrName
     *        name of the concerned attribute.
     * @param oppBehavior
     *        list of lists of interfaces in the CATBehaviorSpecs format.This parameter
     *        has to be deleted by the caller.
     *        <br> this list is a combination of interfaces implemented by the object 
     *         valuating the attribute.
     */     
   HRESULT GetRequestedBehavior(const CATUnicodeString* ipAttrId, CATBehaviorSpecs** oppBehavior);

 private:

    // Copy constructor, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMmrCombineCurveAttrBehavior(const CAAEMmrCombineCurveAttrBehavior &iObjectToCopy);

    // Assignment operator, not implemented
    // Set as private to prevent from compiler automatic creation as public.
    CAAEMmrCombineCurveAttrBehavior & operator = (const CAAEMmrCombineCurveAttrBehavior &iObjectToCopy);

};

#endif
