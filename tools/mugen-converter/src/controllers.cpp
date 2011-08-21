#include "controllers.h"
#include "triggers.h"

#include "ast/all.h"

#include <sstream>

using namespace Mugen;

Content getController(const std::string & type){
    if (match(type, "AfterImage")){
    } else if (match(type, "AfterImageTime")){
    } else if (match(type, "AllPalFX")){
    } else if (match(type, "AngleAdd")){
    } else if (match(type, "AngleDraw")){
    } else if (match(type, "AngleMul")){
    } else if (match(type, "AngleSet")){
    } else if (match(type, "AppendToClipboard")){
    } else if (match(type, "AssertSpecial")){
    } else if (match(type, "AttackDist")){
    } else if (match(type, "AttackMulSet")){
    } else if (match(type, "BGPalFX")){
    } else if (match(type, "BindToParent")){
    } else if (match(type, "BindToRoot")){
    } else if (match(type, "BindToTarget")){
    } else if (match(type, "ChangeAnim")){
    } else if (match(type, "ChangeAnim2")){
    } else if (match(type, "ChangeState")){
    } else if (match(type, "ClearClipboard")){
    } else if (match(type, "CtrlSet")){
    } else if (match(type, "DefenceMulSet")){
    } else if (match(type, "DestroySelf")){
    } else if (match(type, "DisplayToClipboard")){
    } else if (match(type, "EnvColor")){
    } else if (match(type, "EnvShake")){
    } else if (match(type, "Explod")){
    } else if (match(type, "ExplodBindTime")){
    } else if (match(type, "FallEnvShake")){
    } else if (match(type, "ForceFeedback")){
    } else if (match(type, "GameMakeAnim")){
    } else if (match(type, "Gravity")){
    } else if (match(type, "Helper")){
    } else if (match(type, "HitAdd")){
    } else if (match(type, "HitBy")){
    } else if (match(type, "HitDef")){
    } else if (match(type, "HitFallDamage")){
    } else if (match(type, "HitFallSet")){
    } else if (match(type, "HitFallVel")){
    } else if (match(type, "HitOverride")){
    } else if (match(type, "HitVelSet")){
    } else if (match(type, "LifeAdd")){
    } else if (match(type, "LifeSet")){
    } else if (match(type, "MakeDust")){
    } else if (match(type, "ModifyExplod")){
    } else if (match(type, "MoveHitReset")){
    } else if (match(type, "NotHitBy")){
    } else if (match(type, "Null")){
        Content null(3,"# Disabled or invalid controller.");
        null.addLine(3, "pass");
        return null;
    } else if (match(type, "Offset")){
    } else if (match(type, "PalFX")){
    } else if (match(type, "ParentVarAdd")){
    } else if (match(type, "ParentVarSet")){
    } else if (match(type, "Pause")){
    } else if (match(type, "PlaySnd")){
    } else if (match(type, "PlayerPush")){
    } else if (match(type, "PosAdd")){
    } else if (match(type, "PosFreeze")){
    } else if (match(type, "PosSet")){
    } else if (match(type, "PowerAdd")){
    } else if (match(type, "PowerSet")){
    } else if (match(type, "Projectile")){
    } else if (match(type, "RemapPal")){
    } else if (match(type, "RemoveExplod")){
    } else if (match(type, "ReversalDef")){
    } else if (match(type, "ScreenBound")){
    } else if (match(type, "SelfState")){
    } else if (match(type, "SndPan")){
    } else if (match(type, "SprPriority")){
    } else if (match(type, "StateTypeSet")){
    } else if (match(type, "StopSnd")){
    } else if (match(type, "SuperPause")){
    } else if (match(type, "TargetBind")){
    } else if (match(type, "TargetDrop")){
    } else if (match(type, "TargetFacing")){
    } else if (match(type, "TargetLifeAdd")){
    } else if (match(type, "TargetPowerAdd")){
    } else if (match(type, "TargetState")){
    } else if (match(type, "TargetVelAdd")){
    } else if (match(type, "TargetVelSet")){
    } else if (match(type, "Trans")){
    } else if (match(type, "Turn")){
    } else if (match(type, "VarAdd")){
    } else if (match(type, "VarRandom")){
    } else if (match(type, "VarRangeSet")){
    } else if (match(type, "VarSet")){
    } else if (match(type, "VelAdd")){
    } else if (match(type, "VelMul")){
    } else if (match(type, "VelSet")){
    } else if (match(type, "VictoryQuote")){
    } else if (match(type, "Width")){
    } else {
        std::cout << "Unhandled Controller Type: " << type << std::endl;
    }
    
    // Set to pass if state controller can't be determined
    return Content(3, "pass");
}

StateParameterMap::StateParameterMap(){
}

StateParameterMap::StateParameterMap(const StateParameterMap & copy){
    this->parameters = copy.parameters;
    this->triggerall = copy.triggerall;
    this->triggers = copy.triggers;
    this->vars = copy.vars;
}

StateParameterMap::~StateParameterMap(){
}

const StateParameterMap & StateParameterMap::operator=(const StateParameterMap & copy){
    this->parameters = copy.parameters;
    this->triggerall = copy.triggerall;
    this->triggers = copy.triggers;
    this->vars = copy.vars;
    return *this;
}

void StateParameterMap::addTriggerall(Ast::AttributeSimple * simple){
    triggerall.push_back(simple);
}
void StateParameterMap::addTrigger(int number, Ast::AttributeSimple * simple){
    triggers[number].push_back(simple);
}
void StateParameterMap::addVar(Ast::AttributeSimple *simple){
    vars.push_back(simple);
}

void StateParameterMap::add(const std::string & param, Ast::AttributeSimple * simple){
    parameters[param].push_back(simple);
}

std::vector<Ast::AttributeSimple *> * StateParameterMap::find(const std::string & param){
    std::map<std::string, std::vector<Ast::AttributeSimple *> >::iterator found = parameters.find(param);
    if (found != parameters.end()){
        return &(*found).second;
    }
    return NULL;
}

void StateParameterMap::addToDefinition(PythonDefinition & definition){
    Content triggerallContent(3, "# Triggerall");
    triggerallContent.addLine(3, "def triggerall(self):");
    std::string tempString;
    for (std::vector<Ast::AttributeSimple *>::iterator i = triggerall.begin(); i != triggerall.end(); ++i){
        Ast::AttributeSimple * simple = (*i);
        ExpressionBuilder builder = TriggerHandler::convert(*simple->getValue());
        Trigger trigger = Trigger(builder);
        const std::vector<Content> & functions = trigger.getFunctions();
        for (std::vector<Content>::const_iterator j = functions.begin(); j != functions.end(); ++j){
            definition.addContent(*j);
        }
        tempString += trigger.getName() + " and ";
    }
    triggerallContent.addLine(4, (tempString.empty() ? "return 1" : "return (" + tempString.substr(0, tempString.size()-5) + ")"));
    definition.addContent(triggerallContent);
    
    Content allTriggers(3, "# Check all triggers");
    allTriggers.addLine(3, "def checkAll(self):");
    tempString.clear();
    for (int i = 1; ; ++i){
        std::map<int, std::vector<Ast::AttributeSimple *> >::iterator trigger = triggers.find(i);
        if (trigger != triggers.end()){
            std::ostringstream number;
            number << i;
            Content triggerContent(3, "# Trigger " + number.str());
            triggerContent.addLine(3, "def trigger" + number.str() +"(self):");
            std::string triggerString;
            for (std::vector<Ast::AttributeSimple *>::iterator i = trigger->second.begin(); i != trigger->second.end(); ++i){
                Ast::AttributeSimple * simple = (*i);
                ExpressionBuilder builder = TriggerHandler::convert(*simple->getValue());
                Trigger trigger = Trigger(builder);
                const std::vector<Content> & functions = trigger.getFunctions();
                for (std::vector<Content>::const_iterator j = functions.begin(); j != functions.end(); ++j){
                    definition.addContent(*j);
                }
                triggerString += "(triggerall() and " + trigger.getName() + ")" + " and ";
            }
            triggerContent.addLine(4, (triggerString.empty() ? "return 1" : "return (" + triggerString.substr(0, triggerString.size()-5) + ")"));
            definition.addContent(triggerContent);
            
            tempString += "trigger" + number.str() + "() or ";
        } else {
            // No triggers were added
            break;
        }
    }
    // checkAll
    allTriggers.addLine(4, (tempString.empty() ? "return 1" : "return (" + tempString.substr(0, tempString.size()-3) + ")"));
    definition.addContent(allTriggers);
    
    Content allContent(3, "# Check all triggers");
    allContent.addLine(3, "if checkAll() != 1:");
    allContent.addLine(4, "return");
    definition.addContent(allContent);
    
    /* FIXME What to do here? */
    for (std::vector<Ast::AttributeSimple *>::iterator i = vars.begin(); i != vars.end(); ++i){
        Ast::AttributeSimple * simple = (*i);
        ExpressionBuilder builder = TriggerHandler::convert(*simple->getValue());
        Trigger trigger = Trigger(builder);
        const std::vector<Content> & functions = trigger.getFunctions();
        for (std::vector<Content>::const_iterator j = functions.begin(); j != functions.end(); ++j){
            definition.addContent(*j);
        }
    }
}
    
StateControllerStore::StateControllerStore(){
}
StateControllerStore::~StateControllerStore(){
}

void StateControllerStore::newController(){
    controllerParameters.push_back(StateParameterMap());
}

StateParameterMap & StateControllerStore::getCurrentController(){
    return controllerParameters.back();
}

void StateControllerStore::addToDefinition(PythonDefinition & definition){
    
    // TODO Go through current parameters and create new classes based on 'type' and add to definition
    int controller = 0;
    for (std::vector<StateParameterMap>::iterator i = controllerParameters.begin(); i != controllerParameters.end(); ++i){
        std::ostringstream out;
        out << controller;
        definition.addSpace();
        definition.addContent(Content(1, "class controller" + out.str() + "(self, player, world):"));
        definition.addContent(Content(2, "def run(self):"));
        std::vector<Ast::AttributeSimple *> * type = (*i).find("type");
        if (type != NULL){
            std::ostringstream line;
            const std::string & ctrl = type->back()->valueAsString();
            line << "# Found controller type '" << ctrl << "' on line " << type->back()->getLine();
            definition.addContent(Content(3, line.str()));
            definition.addContent(getController(ctrl));
            (*i).addToDefinition(definition);
        }
        definition.addContent(Content(1, "ctrl" + out.str() + " = controller" + out.str() + "()"));
        definition.addContent(Content(1, "ctrl" + out.str() + ".run()"));
        controller++;
    }
}
    
StateController::StateController(const StateParameterMap & parameters):
parameters(parameters){
}

StateController::~StateController(){
}