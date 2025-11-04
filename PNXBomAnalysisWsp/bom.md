### Bom in markdown format
- ProductAlias : 1001

    |    index | property         | value          |
    | -------- | ---------------- | -------------- |
    | 1 | PartNumber  | 1001 |
    | 2 | Revision  | 001 |
    | 3 | Source  | Made |
    | 4 | Definition  | S |
    | 5 | Nomenclature  | Œ“µƒ√Ë ˆ |
    | 6 | DscriptionRef  |  |
    | 7 | InstanceName  | 1001 |
    | 8 | DescriptionInst |  |
    | 9 | ActivateBOM  | 1 |
    | 10 | ProductAlias  | 1001 |
    | 11 | ParentPartNumber |  |
- ProductAlias : 1002

    |    index | property         | value          |
    | -------- | ---------------- | -------------- |
    | 1 | PartNumber  | 1002 |
    | 2 | Revision  | 001 |
    | 3 | Source  | Made |
    | 4 | Definition  | S |
    | 5 | Nomenclature  | ≤‚ ‘3 |
    | 6 | DscriptionRef  |  |
    | 7 | InstanceName  | 1002 |
    | 8 | DescriptionInst |  |
    | 9 | ActivateBOM  | 0 |
    | 10 | ProductAlias  | 1002 |
    | 11 | ParentPartNumber | 1001 |
- ProductAlias : 1002

    |    index | property         | value          |
    | -------- | ---------------- | -------------- |
    | 1 | PartNumber  | 1002 |
    | 2 | Revision  | 001 |
    | 3 | Source  | Made |
    | 4 | Definition  | S |
    | 5 | Nomenclature  | ≤‚ ‘3 |
    | 6 | DscriptionRef  |  |
    | 7 | InstanceName  | 1002 |
    | 8 | DescriptionInst |  |
    | 9 | ActivateBOM  | 0 |
    | 10 | ProductAlias  | 1002 |
    | 11 | ParentPartNumber | 1001 |
- PNXBomAnalysisCmd::OnOutputBomCB 1
### Bom in JsonL format
```json
{"PartNumber":"1001","Revision":"001","Source":"Made","Definition":"S","Nomenclature":"Œ“µƒ√Ë ˆ","DscriptionRef":"","InstanceName":"1001","DescriptionInst":"","ActivateBOM":"1","ProductAlias":"1001","ParentPartNumber":""}
{"PartNumber":"1002","Revision":"001","Source":"Made","Definition":"S","Nomenclature":"≤‚ ‘3","DscriptionRef":"","InstanceName":"1002","DescriptionInst":"","ActivateBOM":"0","ProductAlias":"1002","ParentPartNumber":"1001"}
{"PartNumber":"1002","Revision":"001","Source":"Made","Definition":"S","Nomenclature":"≤‚ ‘3","DscriptionRef":"","InstanceName":"1002","DescriptionInst":"","ActivateBOM":"0","ProductAlias":"1002","ParentPartNumber":"1001"}
```