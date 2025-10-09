// COPYRIGHT DASSAULT SYSTEMES 2000
#ifndef CAAIMmrCombinedCurve_H
#define CAAIMmrCombinedCurve_H

// Local Framework
#include "CAAMmrCombinedCurve.h"

// System Framework
#include "CATBaseUnknown.h"

class CATISpecObject;

extern ExportedByCAAMmrCombinedCurve IID IID_CAAIMmrCombinedCurve ;

/**
 * Interface to manage Combined Curves.
 *  
 *  Role : use this interface to get / set the input of a Combined Curve. 
 *         A Combined Curve is the intersection of two extruded surfaces.
 */

class ExportedByCAAMmrCombinedCurve CAAIMmrCombinedCurve: public CATBaseUnknown
{
  CATDeclareInterface;

  public:

   /**
   * Sets one of the input FirstPoint of the Combined Curve.
   *
   * param ipValue : the FirstPoint
   *
   * returns       : S_OK  the call succeeded.
   *               : E_FAIL  the call failed.
   */
   virtual HRESULT SetFirstPoint ( CATISpecObject *ipValue ) = 0 ;


  /**
   * Gets one of the FirstPoint of the Combined Curve.
   *
   * param opValue : the FirstPoint
   *
   * returns       : S_OK  the call succeeded.
   *               : E_FAIL  the call failed.
   */
   virtual HRESULT GetFirstPoint ( CATISpecObject **opValue ) = 0 ;

  /**
   * Sets MainDir of the Combined Curve.
   *
   * param ipValue : the MainDir
   *
   * returns           : S_OK  the call succeeded.
   *                   : E_FAIL  the call failed.
   */
  virtual HRESULT SetMainDir (CATISpecObject *ipValue ) = 0 ;
  

   /**
   * Gets one of the MainDir of the Combined Curve.
   *
   * param oppValue : the MainDir
   *
   * returns           : S_OK  the call succeeded.
   *                   : E_FAIL  the call failed.
   */
  virtual HRESULT GetMainDir (CATISpecObject **opValue) = 0 ;


};

#endif
