#ifndef PNXUniqueDefine_H
#define PNXUniqueDefine_H

/**
 * @brief define Class Macro to adapt V5 and V6
 */
#ifdef CATIAR424
#define PNXIMechanicalFeature CATIMmiMechanicalFeature
#define PNXIMechanicalFeature_var CATIMmiMechanicalFeature_var
#define IID_PNXIMechanicalFeature IID_CATIMmiMechanicalFeature
#else //  CATIAV5R19
#define PNXIMechanicalFeature CATISpecObject
#define PNXIMechanicalFeature_var CATISpecObject_var
#define IID_PNXIMechanicalFeature IID_CATISpecObject
#endif
#endif
