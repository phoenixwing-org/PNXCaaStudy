// COPYRIGHT DASSAULT SYSTEMES 2000

// Local  Framework
#include "PNXCombinedCurveCmd.h"
#include "PNXCombinedCurveDlg.h" // needed to create an edition dialog box
#include "PNXSubCurveDlg.h"

// PNXCombinedCurve.edu framework
#include "PNXICombinedCurve.h" // needed to query the Combined Curve about its inputs ( edition mode )
#include "PNXICombinedCurveFactory.h" // needed to create a Combined Curve ( creation mode )

// ApplicationFrame Framework
#include "CATFrmEditor.h" // needed to retrieve the editor and then to highight objects

// Dialog Framework
#include "CATDlgDialog.h" // needed to return the dialog box to GiveMyPanel method of
                          // father class CATMMUiPanelStateCommand
// DialogEngine Framework
#include "CATDialogState.h"
#include "CATFeatureImportAgent.h" // needed to be able to pick any element whatever its context is
#include "CATStateActivateNotification.h" // to distinguish begin/resume state in the command activation

// ObjectModelerBase Framework
#include "CATIContainer.h" // needed to create a GS (Geometrical Set)

// ObjectSpecsModeler Framework
#include "CATIDescendants.h" // needed to aggregate the newly created combined curve
#include "CATISpecObject.h"  // needed to manage feature

// InteractiveInterfaces
#include "CATIBuildPath.h" // needed to build a path element to highlight a feature

// MechanicalModeler Framework
#include "CATIBasicTool.h"                   // To retrieve the current tool
#include "CATIGSMTool.h"                     // GSMTool and HybridBody features
#include "CATIMechanicalRootFactory.h"       // needed to create a GS
#include "CATIMmiGeometricalSet.h"           // Only for GSMTool feature
#include "CATIMmiNonOrderedGeometricalSet.h" // Only for GS feature

// MechanicalModelerUI Framework
#include "CATMmrLinearBodyServices.h" // To insert in ordered and linear body
#include "CATPrtUpdateCom.h" // needed to update the feature according to the user's update settings

// MecModInterfaces Framework
#include "CATIPrtPart.h"   // needed to look for a GSM tool
#include "CATMfBRepDefs.h" // needed to declare the modes of BRep feature creation

// Visualization Framework
#include "CATHSO.h"            // needed to highlight objects
#include "CATIVisProperties.h" // needed to change Combined Curve's graphical appearance
#include "CATPathElement.h"    // needed to highlight objects
#include "CATVisPropertiesValues.h"
#include "iostream.h"

// System framework
#include "CATBoolean.h"
#include "CATGetEnvValue.h" // To define the type of development
#include "CATLib.h"

// This command is used by a CATCommandheader
#include "CATCreateExternalObject.h"
CATCreateClass(PNXCombinedCurveCmd);

// auto code
#include "KTCAutoDefine.h"
#include "KTCAutoGSM.h"
#include "KTCAutoObject.h"

//-----------------------------------------------------------------------------
// PNXCombinedCurveCmd : constructor
// Deriving from CATMMUIPanelStateCmd provides an association between
// the states of the command and the Ok/Cancel button.
//-----------------------------------------------------------------------------
PNXCombinedCurveCmd::PNXCombinedCurveCmd(PNXICombinedCurve* ipiCombinedCurve)
    : CATMMUIPanelStateCmd("CombinedCurveCommand")
    , _pFirstPointAgent(NULL)
    , _pMainDirAgent(NULL)
    , _pFirstPointFieldAgent(NULL)
    , _pPushButtonSaveJsonAgent(NULL)
    , _pMainDirFieldAgent(NULL)
    , _piSpecOnFirstPoint(NULL)
    , _piSpecOnMainDir(NULL)
    , feature(NULL_var)
    , _panel(NULL)
    , _ActiveField(0) {
    cout << "### " << __FUNCTION__ << endl;

    mode_ = 1; // creation mode

    if (ipiCombinedCurve != NULL) {
        // Edition mode.
        mode_ = 0;

        // Memorises what curve is being edited.
        feature = ipiCombinedCurve;

        // Reads the inputs of the Combined Curve.
    }

    HRESULT rc = E_FAIL;
    if (!!feature) {
        rc = feature->GetFirstPoint(&_piSpecOnFirstPoint);
        if (FAILED(rc)) return;

        rc = feature->GetMainDir(&_piSpecOnMainDir);
        if (FAILED(rc)) return;
    }
    // creates the dialog box
    _panel = new PNXCombinedCurveDlg();

    // builds the dialog box
    // ! do not call panel->Build from the panel constructor
    _panel->Build();

    // To manage the highlight of the Combined Curve and the UI active object that
    // is used to agregate the Combined Curve at the right place.
    catFrmEditor_ = CATFrmEditor::GetCurrentEditor();
    _HSO          = NULL;
    if (NULL != catFrmEditor_) {
        _HSO = catFrmEditor_->GetHSO();
    }

    // Fills in the dialog panel fields.
    UpdatePanelFields();

    // Checks whether the OK button can be pressed.
    CheckOKSensitivity();
}

//-----------------------------------------------------------------------------
// PNXCombinedCurveCmd : destructor
//-----------------------------------------------------------------------------
PNXCombinedCurveCmd::~PNXCombinedCurveCmd() {
    cout << "### " << __FUNCTION__ << endl;

    // Releases member data pointers before leaving.

    // feature = NULL_var
    KTCRelease(_piSpecOnFirstPoint); // 手动释放
    KTCRelease(_piSpecOnMainDir);    // 手动释放
    KTCRequestDelayedDestruction(_pFirstPointAgent);
    KTCRequestDelayedDestruction(_pMainDirAgent);
    KTCRequestDelayedDestruction(_pFirstPointFieldAgent);
    KTCRequestDelayedDestruction(_pPushButtonSaveJsonAgent);
    KTCRequestDelayedDestruction(_pMainDirFieldAgent);
    KTCRequestDelayedDestruction(_panel);
    catFrmEditor_ = NULL;
    _HSO          = NULL;
}

//-----------------------------------------------------------------------------
// PNXCombinedCurveCmd : BuildGraph()
//-----------------------------------------------------------------------------
void PNXCombinedCurveCmd::BuildGraph() {
    // Agent Creation
    _pFirstPointAgent =
        new CATFeatureImportAgent("FirstPointAgent", NULL, NULL, MfNoDuplicateFeature);
    _pMainDirAgent = new CATFeatureImportAgent("MainDirAgent", NULL, NULL, MfNoDuplicateFeature);
    _pFirstPointFieldAgent    = new CATDialogAgent("FirstPointActiveFieldAgent");
    _pMainDirFieldAgent       = new CATDialogAgent("MainDirActiveFieldAgent");
    _pPushButtonSaveJsonAgent = new CATDialogAgent("ButtonSaveJsonAgent");

    //-----------------------------------------------------------------------------
    // Selection Agents
    //-----------------------------------------------------------------------------

    // _pFirstPointAgent to select a point
    _pFirstPointAgent->SetOrderedElementType("CATIMfZeroDimResult");
    _pFirstPointAgent->AddOrderedElementType("CATPoint");
    _pFirstPointAgent->AddOrderedElementType("CATIGSMPoint");
    _pFirstPointAgent->SetBehavior(CATDlgEngWithPrevaluation | CATDlgEngWithCSO | CATDlgEngOneShot);
    _pFirstPointAgent->SetAgentBehavior(MfPermanentBody | MfLastFeatureSupport |
                                        MfRelimitedFeaturization);

    // _pMainDirAgent to select a direction
    _pMainDirAgent->SetOrderedElementType("CATIMfLine");
    _pMainDirAgent->AddOrderedElementType("CATLine");
    _pMainDirAgent->SetBehavior(CATDlgEngWithPrevaluation | CATDlgEngWithCSO); //|CATDlgEngOneShot);
    _pMainDirAgent->SetAgentBehavior(MfPermanentBody | MfLastFeatureSupport |
                                     MfRelimitedFeaturization);

    // Setting an ID to be able to read the created import
    GUID guid = {/* c17e43d3-2b56-4753-bfe5-bb5f289e2091 */
                 0xc17e43d3,
                 0x2b56,
                 0x4753,
                 {0xbf, 0xe5, 0xbb, 0x5f, 0x28, 0x9e, 0x20, 0x91}};

    _pMainDirAgent->SetImportApplicativeId(guid);

    // _pCurveFieldAgent and _pMainDirFieldAgent to change current acquisition type
    CATDlgSelectorList* pList = _panel->GetField(PNXCopyStudyFieldFirstPoint);
    if (pList) _pFirstPointFieldAgent->AcceptOnNotify(pList, pList->GetListSelectNotification());

    pList = _panel->GetField(PNXCopyStudyFieldMainDir);
    if (pList) _pMainDirFieldAgent->AcceptOnNotify(pList, pList->GetListSelectNotification());

    // Use Agent Mode: _pPushButtonSaveJsonAgent to save the a file:
    _pPushButtonSaveJsonAgent->AcceptOnNotify(
        _panel->_pushButtonSaveJson, _panel->_pushButtonSaveJson->GetPushBActivateNotification());

    // AddAnalyseNotificationCB Mode: Action for ButtonDirectCallback
    // 第4个参数为 data： 64位指针，CATLONG32ToPtr 是把整数转为指针进行传递
    AddAnalyseNotificationCB(_panel->_pushButtonDirectCallback,
                             _panel->_pushButtonDirectCallback->GetPushBActivateNotification(),
                             (CATCommandMethod)&PNXCombinedCurveCmd::OnPushButtonCB,
                             CATLONG32ToPtr(PNXCopyStudyActionDirectCallback));

    AddAnalyseNotificationCB(_panel->_pushButtonSubDialog,
                             _panel->_pushButtonSubDialog->GetPushBActivateNotification(),
                             (CATCommandMethod)&PNXCombinedCurveCmd::OnPushButtonCB,
                             CATLONG32ToPtr(PNXCopyStudyActionSubDialog));

    //-----------------------------------------------------------------------------
    // Command States
    //-----------------------------------------------------------------------------

    // Uses "PanelStates" instead of standard "DialogStates".
    // Theses states are provided by father class CATMMUIPanelStateCommand.
    // They make it possible for you not to worry about transition to OK and Cancel States.

    // Curve selection state
    CATDialogState* WaitForCurveState =
        GetInitialPanelState("Select a Point, Dir or another input field");
    WaitForCurveState->AddDialogAgent(_pFirstPointAgent);
    WaitForCurveState->AddDialogAgent(_pFirstPointFieldAgent);
    WaitForCurveState->AddDialogAgent(_pMainDirAgent);
    WaitForCurveState->AddDialogAgent(_pMainDirFieldAgent);
    WaitForCurveState->AddDialogAgent(_pPushButtonSaveJsonAgent);

    //-----------------------------------------------------------------------------
    // Transitions
    //-----------------------------------------------------------------------------

    // From Curve to Curve ( click on several curves to change of curve )
    AddTransition(WaitForCurveState, WaitForCurveState, IsOutputSetCondition(_pFirstPointAgent),
                  Action((ActionMethod)&PNXCombinedCurveCmd::PointSelected));

    AddTransition(WaitForCurveState, WaitForCurveState, IsOutputSetCondition(_pMainDirAgent),
                  Action((ActionMethod)&PNXCombinedCurveCmd::DirectionSelected));

    AddTransition(WaitForCurveState, WaitForCurveState,
                  IsOutputSetCondition(_pFirstPointFieldAgent),
                  Action((ActionMethod)&PNXCombinedCurveCmd::FirstPointFieldSelected));

    AddTransition(WaitForCurveState, WaitForCurveState,
                  IsOutputSetCondition(_pPushButtonSaveJsonAgent),
                  Action((ActionMethod)&PNXCombinedCurveCmd::OnPushButtonSaveJsonAgent));

    // to MainDir
    AddTransition(WaitForCurveState, WaitForCurveState, IsOutputSetCondition(_pMainDirFieldAgent),
                  Action((ActionMethod)&PNXCombinedCurveCmd::MainDirFieldSelected));
}

//-----------------------------------------------------------------------------
// PNXCombinedCurveCmd : GiveMyPanel()
//-----------------------------------------------------------------------------
CATDlgDialog* PNXCombinedCurveCmd::GiveMyPanel() {
    // Used by father class CATMMUiPanelStateCommand to be notified of events
    // sent by the OK and CANCEl press button.
    return (_panel);
}

//-----------------------------------------------------------------------------
// PNXCombinedCurveCmd : CancelAction()
//-----------------------------------------------------------------------------
CATBoolean PNXCombinedCurveCmd::CancelAction(void*) {
    // Unset Repeat mode  when cancel or close is clicked
    if (catFrmEditor_) catFrmEditor_->UnsetRepeatedCommand();
    return TRUE;
}

//-----------------------------------------------------------------------------
// PNXCombinedCurveCmd : OkAction()
//-----------------------------------------------------------------------------
CATBoolean PNXCombinedCurveCmd::OkAction(void*) {
    HRESULT rc = E_FAIL;

    // EDS 4/7/2005 (RI 492591): Vider les SO en sortie de commande
    EmptySO();

    //
    // 0- Modifies or creates the CC
    //
    if (0 == GetMode() && !!feature) {
        // Updates the combine with its new curves inputs.
        rc = feature->SetFirstPoint(_piSpecOnFirstPoint);
        if (FAILED(rc)) return FALSE;

        rc = feature->SetMainDir(_piSpecOnMainDir);
        if (FAILED(rc)) return FALSE;
    }
    else {
        rc = CreateCombinedCurve();
    }

    //
    // 2- Updates
    //

    KTCAutoObject::update(_MyFeature, false); // 3. Updates, do not warning

    //
    // 3- Inserts if necessary ( if inside an ordered (and linear) body )
    //
    if (SUCCEEDED(rc)) {
        if (KTCAutoGSM::IsInsideOrderedBody(_MyFeature)) {
            // Invoke the Insert method is mandatory
            CATBaseUnknown_var spBUOnCC = _MyFeature;
            if (!!spBUOnCC) rc = CATMmrLinearBodyServices::Insert(spBUOnCC);
        }
    }

    //
    // 4- Let's give our Combined Curve a better appearance
    //
    if (SUCCEEDED(rc) && (1 == GetMode()) && !!_MyFeature) {
        CATIVisProperties* piGraphPropOnCombinedCurve = NULL;
        rc = _MyFeature->QueryInterface(IID_CATIVisProperties, (void**)&piGraphPropOnCombinedCurve);
        if (SUCCEEDED(rc)) {
            CATVisPropertiesValues Attribut;
            Attribut.SetColor(255, 255, 0); // yellow
            Attribut.SetWidth(4);           // medium thickness
            piGraphPropOnCombinedCurve->SetPropertiesAtt(Attribut, CATVPAllPropertyType, CATVPLine);

            piGraphPropOnCombinedCurve->Release();
            piGraphPropOnCombinedCurve = NULL;
        }
    }

    if (SUCCEEDED(rc))
        return TRUE;
    else
        return FALSE;
}
//-----------------------------------------------------------------------------
CATISpecObject_var PNXCombinedCurveCmd::GiveMyFeature() {
    return _MyFeature;
}
//-----------------------------------------------------------------------------
CATBoolean PNXCombinedCurveCmd::PointSelected(void*) {

    // checks if the selected object must be added ( not  selected yet ) or removed ( already
    // selected ) as input curve
    ElementSelected(_pFirstPointAgent);

    // gets ready for next acquisition
    _pFirstPointAgent->InitializeAcquisition();

    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXCombinedCurveCmd::DirectionSelected(void*) {
    // checks if the selected object must be added ( not  selected yet ) or removed ( already
    // selected ) as input direction
    ElementSelected(_pMainDirAgent);

    // gets ready for next acquisition
    _pMainDirAgent->InitializeAcquisition();

    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXCombinedCurveCmd::FirstPointFieldSelected(void*) {
    static int a = 0;
    cout << "I am in FirstPointFieldSelected(void *)" << a++ << endl;
    // put the focus on the first field of the Combined Curve edition dialog box
    // ( first curve ) and highlight the corresponding geometrical element
    SetActiveField(PNXCopyStudyFieldFirstPoint);

    // gets ready for next acquisition
    _pFirstPointFieldAgent->InitializeAcquisition();

    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXCombinedCurveCmd::MainDirFieldSelected(void*) {
    // put the focus on the second field of the Combined Curve edition dialog box
    // ( first direction ) and highlight the corresponding geometrical element
    SetActiveField(PNXCopyStudyFieldMainDir);

    // gets ready for next acquisition
    _pMainDirFieldAgent->InitializeAcquisition();

    return TRUE;
}
//-----------------------------------------------------------------------------
CATBoolean PNXCombinedCurveCmd::OnPushButtonSaveJsonAgent(void* data) {
    // 把data转为整数
    CATLong mode = CATPtrToLONG32(data);
    cout << "### " << __FUNCTION__ << endl;

    cout << " data = " << data << " to long :" << mode << endl;

    // save to a file
    cout << "- Your code : save json to a file" << endl;

    // gets ready for next acquisition
    _pPushButtonSaveJsonAgent->InitializeAcquisition();
    return TRUE;
}
//-----------------------------------------------------------------------------
void PNXCombinedCurveCmd::OnPushButtonCB(CATCommand* iCmd, CATNotification* iNotif,
                                         CATCommandClientData iData) {
    // 把data转为整数
    CATLong data = CATPtrToINT32(iData);
    cout << "### " << __FUNCTION__ << endl;

    cout << " iData = " << iData << " to long :" << data << endl;

    switch (data) {
    case PNXCopyStudyActionDirectCallback:
        cout << "Action from data 0" << endl;
        break;
    case PNXCopyStudyActionSubDialog:
        cout << "Action from data 1" << endl;

        // 子对话框显示和隐藏切换
        if (_panel && _panel->_subPanel) {
            PNXSubCurveDlg* subPanel = _panel->_subPanel;
            if (subPanel->GetVisibility() != CATDlgShow)
                _panel->_subPanel->SetVisibility(CATDlgShow);
            else
                _panel->_subPanel->SetVisibility(CATDlgHide);
        }

        break;
    default:
        cout << "data error" << endl;
        break;
    }
}
//-----------------------------------------------------------------------------
void PNXCombinedCurveCmd::SetActiveField(int ActiveField) {

    // this method main goal is to show the user that the acquisition
    // is now dedicated to the input field
    _ActiveField = ActiveField;

    // first let's empty current highlighted objects
    if (NULL != _HSO) {
        _HSO->Empty();
    }

    // Gets a pointer on CATISpecObject on the geometrical element to highlight
    CATISpecObject* piSpecOnGeomElem = NULL;
    if (PNXCopyStudyFieldFirstPoint == ActiveField) piSpecOnGeomElem = _piSpecOnFirstPoint;
    if (PNXCopyStudyFieldMainDir == ActiveField) piSpecOnGeomElem = _piSpecOnMainDir;

    if ((piSpecOnGeomElem != NULL) && (NULL != _HSO) && (NULL != catFrmEditor_)) {
        // uses this pointer to build a path element
        CATIBuildPath* piBuildPath = NULL;
        HRESULT rc = piSpecOnGeomElem->QueryInterface(IID_CATIBuildPath, (void**)&piBuildPath);
        if (SUCCEEDED(rc)) {
            CATPathElement  Context      = catFrmEditor_->GetUIActiveObject();
            CATPathElement* pPathElement = NULL;
            rc                           = piBuildPath->ExtractPathElement(&Context, &pPathElement);

            if (pPathElement != NULL) { // the geometrical element corresponding to the active field
                                        // is now highlighted
                _HSO->AddElement(pPathElement);

                pPathElement->Release();
                pPathElement = NULL;
            }

            piBuildPath->Release();
            piBuildPath = NULL;
        }
    }

    _panel->SetActiveField(
        ActiveField); // puts the focus on the Active Field is the Combined Curve edition dialog box
}

//-----------------------------------------------------------------------------
// PNXCombinedCurveCmd : ElementSelected()
//-----------------------------------------------------------------------------
void PNXCombinedCurveCmd::ElementSelected(CATFeatureImportAgent* pAgent) {
    cout << "### " << __FUNCTION__ << endl;

    if ((pAgent == NULL) || (_ActiveField == 0)) return;

    // translates the selection into the good pointer on a CATBaseUnknwon model element
    CATBaseUnknown* pSelection = pAgent->GetElementValue(pAgent->GetValue());

    if (NULL != pSelection) {
        // gets a pointer on CATISpecObject for this element
        CATISpecObject* piSpecOnSelection = NULL;
        HRESULT rc = pSelection->QueryInterface(IID_CATISpecObject, (void**)&piSpecOnSelection);
        if (FAILED(rc)) {
            return;
        }

        // checks whether the selected element is the same than the one "in" the active field
        // o if this element is the same, the user wants to erase his selection.
        // o otherwise, the user wants to replace the old selected element by the new one.
        switch (_ActiveField) {
        case PNXCopyStudyFieldFirstPoint: {
            if (_piSpecOnFirstPoint == piSpecOnSelection) // same one
            {
                _piSpecOnFirstPoint->Release(); // this pointeur is not null
                _piSpecOnFirstPoint = NULL;     // erases the selection
            }
            else {
                if (NULL != _piSpecOnFirstPoint) _piSpecOnFirstPoint->Release();
                _piSpecOnFirstPoint = piSpecOnSelection; // other one, replaces the selection
                _piSpecOnFirstPoint->AddRef();
            }

            break;
        }
        case PNXCopyStudyFieldMainDir: {
            if (_piSpecOnMainDir == piSpecOnSelection) {
                _piSpecOnMainDir->Release(); // this pointeur is not null
                _piSpecOnMainDir = NULL;
            }
            else {
                if (NULL != _piSpecOnMainDir) _piSpecOnMainDir->Release();
                _piSpecOnMainDir = piSpecOnSelection;
                _piSpecOnMainDir->AddRef();
            }
            break;
        }
        }

        piSpecOnSelection->Release();
        piSpecOnSelection = NULL;

        // updates the text corresponding to the feature names in the panel fields
        UpdatePanelFields();

        // ckecks whether the four fields are filled in or not :
        // o if the four fields are filled, the Combined Curve can be created or modified
        //    => the OK button can be pressed
        // o if at least one field is not filled, the Combined Curve can not be created or modified
        //    => The OK button can not be pressed ( it is grayed )
        CheckOKSensitivity();
    }

    return;
}
//-----------------------------------------------------------------------------
void PNXCombinedCurveCmd::CheckOKSensitivity() {
    if (_piSpecOnFirstPoint != NULL && _piSpecOnMainDir != NULL)
        _panel->SetOKSensitivity(CATDlgEnable);
    else
        _panel->SetOKSensitivity(CATDlgDisable);

    return;
}
//-----------------------------------------------------------------------------
void PNXCombinedCurveCmd::UpdatePanelFields() {
    // gets the name of the selected elements and put these names into the Combined Curve edition
    // dialog box relevant text fields

    if (_piSpecOnFirstPoint != NULL)
        _panel->SetName(PNXCopyStudyFieldFirstPoint, _piSpecOnFirstPoint->GetDisplayName());
    else
        _panel->SetName(PNXCopyStudyFieldFirstPoint, CATUnicodeString("no selection"));

    if (_piSpecOnMainDir != NULL)
        _panel->SetName(PNXCopyStudyFieldMainDir, _piSpecOnMainDir->GetDisplayName());
    else
        _panel->SetName(PNXCopyStudyFieldMainDir, CATUnicodeString("no selection"));

    return;
}
//-----------------------------------------------------------------------------
int PNXCombinedCurveCmd::GetMode() {
    // This very simple methods checks if the user is creating or editing the Combined Curve.
    // This data is used by father command CATMMUIPanelStateCommand and by CATPrtUpdateCom.
    // They both provide standard edition command behaviour :
    // for example, it is not possible to create a sick Combined Curve ( a Combined Curve generating
    // an error )

    return mode_; // 0 : edit mode
                  // 1 : creation mode
}
//-----------------------------------------------------------------------------
HRESULT PNXCombinedCurveCmd::CreateCombinedCurve() {
    if (!!feature) return S_OK; // 只能创建一次
    cout << "### " << __FUNCTION__ << endl;

    //
    // 1- Looking for a body to create the Combined Curve
    //
    //

    // CATIGSMTool is implemented by the HybridBody and GSMTool StartUp
    // it is a valid pointer to handle the body which will contain the new
    // Combined Curve
    //
    HRESULT      rc          = E_FAIL;
    CATIGSMTool* piGSMTool   = NULL;
    char*        pCombCrvOGS = NULL;
    CATLibStatus result      = ::CATGetEnvValue("CAAMmrCombCrvOGS", &pCombCrvOGS);
    if ((CATLibError == result) || (NULL == pCombCrvOGS)) {
        char* pCombCrvNoHybridBody = NULL;
        result = ::CATGetEnvValue("CAAMmrCombCrvNoHybridBody", &pCombCrvNoHybridBody);
        if ((CATLibError == result) || (NULL == pCombCrvNoHybridBody)) {
            // Looking for or creating only a Geometrical Set
            // The result cannot be an ordered geometrical set or an hybrid body
            //
            rc = KTCAutoGSM::LookingForGeomSet(catFrmEditor_, &piGSMTool);
        }
        else {
            free(pCombCrvNoHybridBody);
            pCombCrvNoHybridBody = NULL;

            // Looking for an OGS or a GS, or creating a Geometrical Set
            // The result cannot be an hybrid body
            //
            rc = KTCAutoGSM::LookingForGeomSetOrOrderedGeomSet(catFrmEditor_, &piGSMTool);
        }
    }
    else {
        free(pCombCrvOGS);
        pCombCrvOGS = NULL;

        // Looking for any type of mechanical bodies, or creating a Geometrical Set
        // The result cannot be a former solid body
        //
        rc = KTCAutoGSM::LookingForAnyTypeOfBody(catFrmEditor_, &piGSMTool);
    }

    //
    // 2- Creating the Combined Curve
    //
    CATISpecObject* piSpecOnCombinedCurve = NULL;

    if (SUCCEEDED(rc) && (NULL != piGSMTool)) {
        //
        // Uses PNXICombinedCurveFactory implemented by CATPrtCont
        //
        CATISpecObject_var piSpecObjOnTool = piGSMTool;
        if (NULL_var != piSpecObjOnTool) {
            // GetFeatContainer for a mechanical feature
            // is CATPrtCont, the specification container
            CATIContainer_var spContainer = piSpecObjOnTool->GetFeatContainer();

            if (NULL_var != spContainer) {
                PNXICombinedCurveFactory* piCombinedCurveFactory = NULL;
                rc = spContainer->QueryInterface(IID_PNXICombinedCurveFactory,
                                                 (void**)&piCombinedCurveFactory);
                if (SUCCEEDED(rc)) {
                    // creates the Combined Curve

                    rc = piCombinedCurveFactory->CreateCombinedCurve(
                        _piSpecOnFirstPoint, _piSpecOnMainDir, &piSpecOnCombinedCurve);

                    // 检出到feature
                    if (SUCCEEDED(rc)) {
                        rc = piSpecOnCombinedCurve->QueryInterface(IID_PNXICombinedCurve,
                                                                   (void**)&feature);
                    }

                    piCombinedCurveFactory->Release();
                    piCombinedCurveFactory = NULL;
                }
            }
            else
                rc = E_FAIL;
        }
        else
            rc = E_FAIL;
    }

    _MyFeature = feature; // set to My Feature

    //
    // 3- Aggregating the newly Combined Curve in the Geometrical Set
    //
    if (SUCCEEDED(rc) && (NULL != piGSMTool) && (NULL != piSpecOnCombinedCurve)) {
        CATIDescendants* pIDescendantsOnGSMTool = NULL;
        rc = piGSMTool->QueryInterface(IID_CATIDescendants, (void**)&pIDescendantsOnGSMTool);
        if (SUCCEEDED(rc)) {
            // Checks the type of the GSMTool
            //
            int TypeOrderedBody = -1;
            piGSMTool->GetType(TypeOrderedBody);

            if (1 ==
                TypeOrderedBody) { // OGS/HB : the CC is set after the current feature or at the end
                //       of the set, if the current feature is the set itself
                //
                cout << " Ordered and linear body " << endl;
                int                pos        = 0;
                CATISpecObject_var CurrentElt = GetCurrentFeature();
                if (NULL_var != CurrentElt) {
                    pos = pIDescendantsOnGSMTool->GetPosition(CurrentElt);
                }

                if (0 == pos) {
                    // The current feature is the GSMTool itself
                    // the CC is appended at the end
                    pIDescendantsOnGSMTool->Append(_MyFeature);
                }
                else {
                    // the current feature is inside the GSMTool
                    // the CC is appended just below it (which can be at the end)
                    pIDescendantsOnGSMTool->AddChild(_MyFeature, pos + 1);
                }
            }
            else { // GS : the CC is set at the end of the set
                cout << " GS case " << endl;
                pIDescendantsOnGSMTool->Append(_MyFeature);
            }

            KTCRelease(pIDescendantsOnGSMTool); // 手动释放
        }
    }

    KTCRelease(piGSMTool); // 手动释放

    return rc;
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXCombinedCurveCmd::Activate(CATCommand* iCmd, CATNotification* iNotif) {
    // cout << "### " << __FUNCTION__ << endl;

    // Sets the CC as the current feature
    // only in edition mode and if the CC is inside an ordered body
    //
    if ((NULL != iNotif) && (0 == GetMode()) && !!_MyFeature) {
        if (KTCAutoGSM::IsInsideOrderedBody(_MyFeature)) {
            // In case of first activation, SetCombCrvAsCurrentFeature will
            // keep the feature to restore at the end of the command

            if (((CATStateActivateNotification*)iNotif)->GetType() ==
                CATStateActivateNotification::Begin) {
                // GetCurrentFeature is a method of CATMMUIStateCommand
                featurePrevious_ = GetCurrentFeature();
            }

            // Sets the CC as current - method of CATMMUIStateCommand
            SetCurrentFeature(_MyFeature);
        }
    }
    return (CATStatusChangeRCCompleted);
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXCombinedCurveCmd::Deactivate(CATCommand* iCmd, CATNotification* iNotif) {
    // cout << "### " << __FUNCTION__ << endl;

    // Restores the old current feature
    // only in edition mode and if the CC is inside an ordered body
    //
    if (0 == GetMode() && KTCAutoGSM::IsInsideOrderedBody(_MyFeature)) {
        // method of CATMMUIStateCommand
        SetCurrentFeature(featurePrevious_);
    }

    return (CATStatusChangeRCCompleted);
}
//-----------------------------------------------------------------------------
CATStatusChangeRC PNXCombinedCurveCmd::Cancel(CATCommand* iCmd, CATNotification* iNotif) {
    // cout << "### " << __FUNCTION__ << endl;

    // Check if the CC is inside an ordered body
    if (KTCAutoGSM::IsInsideOrderedBody(_MyFeature)) {
        // Restores the old current feature in edition mode
        // and if the CC is inside an ordered body
        if ((0 == GetMode())) {
            // method of CATMMUIStateCommand
            SetCurrentFeature(featurePrevious_);
        }
        // Set the newly CC as the current feature in creation mode
        // and if the CC is inside an ordered body
        else { // if ((1 == GetMode()))
            // Sets the CC as current - method of CATMMUIStateCommand
            if (!!_MyFeature) SetCurrentFeature(_MyFeature);
        }
    }

    return CATMMUIPanelStateCmd::Cancel(iCmd, iNotif);
}
