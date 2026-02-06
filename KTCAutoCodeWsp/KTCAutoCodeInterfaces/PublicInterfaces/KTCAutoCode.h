/**
 * @copyright   Shanghai Kuntai Software Technology Co., Ltd. 2025
 * @license     MIT
 * @file        KTCAutoCode.h
 * @note        Kt CAA Auto Code
 */
#ifndef _KTCAutoCode_H_
#define _KTCAutoCode_H_

// Kt CAA Auto Code

// for class define
class KTCAutoSelectorCtx;
// pre-declare CAT
class CATPathElementAgent;
class CATFeatureImportAgent;
class CATOtherDocumentAgent;
class CATPathElementAgent;
class CATISpecObject;
class CATMMUIPanelStateCmd;
class CATHSO;
class CATISO;
class CATIGSMTool;
class CATIPrtPart;
class CATDialogState;

/**
 * @brief FIELD SET LINE
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_FIELD_SET_LINE KTCAutoDialog::selectorlist_setline

/**
 * @brief Agent Initialize
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_AGENT_INITIALIZE(NAME) _fia##NAME->InitializeAcquisition()

/**
 * @brief HSO Clear.
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_HSO_CLEAR() catHSO_->Empty()

/**
 * @brief HSO Add.
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_HSO_ADD(NAME) ktcHSO_.AddElement(parameter->NAME)

/**
 * @brief CMD ACTION PDA
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_ACTION_PDA(NAME)    \
    _da##NAME->InitializeAcquisition(); \
    if (fieldChange) ktcHSO_.AddElement(parameter->NAME)

/**
 * @brief CMD ACTION FIA
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_ACTION_FIA(NAME)                                           \
    count = ktcHSO_.after_element_selected(_fia##NAME, parameter->NAME, mode); \
    if (0 == count) cout << "Error to Select " << #NAME << "!" << endl;        \
    _fia##NAME->InitializeAcquisition();

/**
 * @brief CMD AGENT FIA CLEAR
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_ACTION_FIA_CLEAR(NAME) catDialogState_->RemoveDialogAgent(_fia##NAME)

/**
 * @brief CMD AGENT BUILD GRAPH, Start Part
 * @param[in] PREFIX a string like KTCBaseSample
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_BUILD_START(PREFIX)      \
    ktcHSO_.initial(catFrmEditor_, catHSO_); \
    dialog->catHSO_              = catHSO_;  \
    CATDlgSelectorList* selector = NULL

/**
 * @brief CMD AGENT BUILD GRAPH, End Part
 * @param[in] PREFIX a string like KTCBaseSample
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_BUILD_END(PREFIX)                                                     \
    daValueChange_ = new CATDialogAgent("ValueChangeAgent");                              \
    dialog->InitialMenuRightClick();                                                      \
    dialog->SetAcceptOnNotifyOfValueChange(daValueChange_);                               \
    catDialogState_->AddDialogAgent(daValueChange_);                                      \
    AddTransition(catDialogState_, catDialogState_, IsOutputSetCondition(daValueChange_), \
                  Action((ActionMethod) & PREFIX##Cmd::ActionValueChange));               \
    daValueChange_->AcceptOnNotify(NULL, KTCAutoValueChangedNtf::ClassName())

/**
 * @brief CMD AGENT BUILD GRAPH, field part
 * @param[in] PREFIX a string like KTCBaseSample
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_BUILD_FIELD(PREFIX, NAME)                                                 \
    selector   = dialog->_SelectorList##NAME;                                                 \
    _ctx##NAME = dialog->regitster_field(Field_##PREFIX##_##NAME, selector, #NAME);           \
    if (NULL == _ctx##NAME || NULL == _ctx##NAME->selector) {                                 \
        msg = " {NG}. for register field " #NAME;                                             \
        cout << msg << endl;                                                                  \
        KTCAutoDialog::ShowMessageBox(1001, msg, dialog);                                     \
        RequestDelayedDestruction();                                                          \
        return;                                                                               \
    }                                                                                         \
    _ctx##NAME->regitster_feature(parameter->NAME);                                           \
    _fia##NAME->SetBehavior(CATDlgEngWithPrevaluation | CATDlgEngWithCSO | CATDlgEngOneShot); \
    _da##NAME = new CATDialogAgent("Pda" #NAME);                                              \
    _da##NAME->AcceptOnNotify(selector, selector->GetListSelectNotification());               \
    catDialogState_->AddDialogAgent(_da##NAME);                                               \
    AddTransition(catDialogState_, catDialogState_, IsOutputSetCondition(_fia##NAME),         \
                  Action((ActionMethod) & PREFIX##Cmd::ActionSelectorListFia, NULL, NULL,     \
                         (void*)Field_##PREFIX##_##NAME));                                    \
    AddTransition(catDialogState_, catDialogState_, IsOutputSetCondition(_da##NAME),          \
                  Action((ActionMethod) & PREFIX##Cmd::ActionSelectorListPda, NULL, NULL,     \
                         (void*)Field_##PREFIX##_##NAME));

/**
 * @brief CMD AGENT BUILD GRAPH FIA, field axis line only
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_BUILD_FIA_AXIS(NAME) KT_AUTO_CMD_BUILD_FIA_LINE(NAME)

/**
 * @brief CMD AGENT BUILD GRAPH FIA, field axis system
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_BUILD_FIA_AXIS_SYSTEM(NAME) \
    KT_AUTO_CMD_BUILD_FIA_NEW(NAME);            \
    _fia##NAME->SetOrderedElementType("CATIMf3DAxisSystem")

/**
 * @brief CMD AGENT BUILD GRAPH FIA, field Curve
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_BUILD_FIA_CURVE(NAME) \
    KT_AUTO_CMD_BUILD_FIA_NEW(NAME);      \
    _fia##NAME->SetOrderedElementType("CATIMfMonoDimResult")

/**
 * @brief CMD AGENT BUILD GRAPH FIA, field default
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_BUILD_FIA_DEFAULT(NAME) \
    KT_AUTO_CMD_BUILD_FIA_NEW(NAME);        \
    _fia##NAME->SetOrderedElementType("CATIMfZeroDimResult")

/**
 * @brief CMD AGENT BUILD GRAPH FIA, field direction
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_BUILD_FIA_DIRECTION KT_AUTO_CMD_BUILD_FIA_LINE

/**
 * @brief CMD AGENT BUILD GRAPH FIA, field face
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_BUILD_FIA_FACE(NAME) \
    KT_AUTO_CMD_BUILD_FIA_NEW(NAME);     \
    _fia##NAME->SetOrderedElementType("CATIMfBiDimResult")

/**
 * @brief CMD AGENT BUILD GRAPH FIA, field support
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_BUILD_FIA_SUPPORT(NAME) \
    KT_AUTO_CMD_BUILD_FIA_NEW(NAME);        \
    _fia##NAME->SetOrderedElementType("CATIMfBiDimResult")

/**
 * @brief CMD AGENT BUILD GRAPH FIA, field My Axis
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_BUILD_FIA_GRID_AXIS(NAME) \
    KT_AUTO_CMD_BUILD_FIA_NEW(NAME);          \
    _fia##NAME->SetOrderedElementType(KTCIGridAxis::ClassName())

/**
 * @brief CMD AGENT BUILD GRAPH FIA, field Line
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_BUILD_FIA_LINE(NAME)                      \
    KT_AUTO_CMD_BUILD_FIA_NEW(NAME);                          \
    _fia##NAME->SetOrderedElementType("CATIMfZeroDimResult"); \
    _fia##NAME->AddOrderedElementType("CATIMfLine");          \
    _fia##NAME->AddOrderedElementType("CATLine")

/**
 * @brief CMD AGENT BUILD GRAPH FIA, field part
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_BUILD_FIA_NEW(NAME)                                        \
    CATFeatureImportAgent* fia##NAME = new CATFeatureImportAgent("Fia" #NAME); \
    _fia##NAME                       = fia##NAME;                              \
    fia##NAME->SetAgentBehavior(MfPermanentBody | MfLastFeatureSupport | MfRelimitedFeaturization)

/**
 * @brief CMD AGENT BUILD GRAPH FIA, field plane
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_BUILD_FIA_PLANE(NAME) \
    KT_AUTO_CMD_BUILD_FIA_NEW(NAME);      \
    _fia##NAME->SetOrderedElementType("CATPlane")

/**
 * @brief CMD AGENT BUILD GRAPH FIA, field Point
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_BUILD_FIA_POINT(NAME)                     \
    KT_AUTO_CMD_BUILD_FIA_NEW(NAME);                          \
    _fia##NAME->SetOrderedElementType("CATIMfZeroDimResult"); \
    _fia##NAME->AddOrderedElementType("CATPoint");            \
    _fia##NAME->AddOrderedElementType("CATVertex")

/**
 * @brief CMD AGENT CONSTRUCTOR, common part
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_AGENT_CONSTRUCTOR_COMMON()                                                 \
    catDialogState_(NULL), daValueChange_(NULL), catFrmEditor_(NULL), catHSO_(NULL), mode_(1), \
        code_(0), parameter(NULL), core(NULL), dialog(NULL), feature(NULL_var)

/**
 * @brief CMD AGENT CONSTRUCTOR, field part
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_AGENT_CONSTRUCTOR_FIELD(NAME) \
    _da##NAME(NULL), _fia##NAME(NULL), _ctx##NAME(NULL)

/**
 * @brief CMD AGENT DECLARE
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_AGENT_DECLARE_COMMON() \
    CATDialogState* catDialogState_;       \
    CATDialogAgent* daValueChange_;        \
    CATFrmEditor*   catFrmEditor_;         \
    CATHSO*         catHSO_;               \
    KTCAutoHSO      ktcHSO_;               \
    int             mode_;                 \
    int             code_

/**
 * @brief CMD AGENT DECLARE, base parameter
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_AGENT_DECLARE_BASE(NAMESPACE, KEYWORDS) \
    NAMESPACE##KEYWORDS##Param*  parameter;                 \
    NAMESPACE##KEYWORDS##Core*   core;                      \
    NAMESPACE##KEYWORDS##Dlg*    dialog;                    \
    NAMESPACE##I##KEYWORDS##_var feature

/**
 * @brief CMD AGENT DECLARE FIELD
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_AGENT_DECLARE_FIELD(NAME) \
    CATDialogAgent*      _da##NAME;           \
    CATPathElementAgent* _fia##NAME;          \
    KTCAutoSelectorCtx*  _ctx##NAME

/**
 * @brief CMD AGENT DESTRUCTOR, common part
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_AGENT_DESTRUCTOR_COMMON()     \
    catFrmEditor_   = NULL;                       \
    catHSO_         = NULL;                       \
    catDialogState_ = NULL;                       \
    feature         = NULL_var;                   \
    KTDelete(core);                               \
    KTDelete(parameter);                          \
    KTCRequestDelayedDestruction(daValueChange_); \
    KTCRequestDelayedDestruction(dialog)

/**
 * @brief CMD AGENT DESTRUCTOR, field part
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_AGENT_DESTRUCTOR_FIELD(NAME) \
    KTCRequestDelayedDestruction(_da##NAME);     \
    KTCRequestDelayedDestruction(_fia##NAME);    \
    _ctx##NAME = NULL

/**
 * @brief CMD AGENT UPDATE STATE
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_AGENT_UPDATE_STATE(NAME)     \
    catDialogState_->AddDialogAgent(_fia##NAME); \
    catDialogState_->SetMessage("Select the " #NAME)

/**
 * @brief CMD AGENT UPDATE STATE ERROR
 * @param[in] NAME a name string
 * @note Kt Auto Code Macro.
 */
#define KT_AUTO_CMD_AGENT_UPDATE_STATE_ERROR() \
    catDialogState_->SetMessage("None Element can select. Please click a Field.")

#endif //_KTCAutoCode_H_
