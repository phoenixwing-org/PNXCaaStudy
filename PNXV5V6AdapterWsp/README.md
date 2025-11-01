# V5 V6适配研究
- 目标
```cpp
#ifdef CATIAR424 
#define  CATIMmiMechanicalFeature CAAIMmiMechanicalFeature
#else //  CATIAV5R19
#define CATISpecObject CAAIMmiMechanicalFeature
#endif
```
- 说明
    - CATIAR424 : for V6 version
    - CATIAV5R19: for V6Version
