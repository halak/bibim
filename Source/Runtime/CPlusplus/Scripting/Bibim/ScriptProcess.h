#pragma once
#ifndef __BIBIM_SCRIPTPROCESS_H__
#define __BIBIM_SCRIPTPROCESS_H__

#   include <Bibim/FWD.h>
#   include <Bibim/SharedObject.h>

    namespace Bibim
    {
        class ScriptProcess : public SharedObject
        {
            BBObjectClass(ScriptProcess, SharedObject, 'S', 'C', 'P', 'S');
            public:
                enum CommandID
                {
                    JumpCommand = 0,
                    IfTrueThenJumpCommand = 1,
                    IfFalseThenJumpCommand = 2,
                    IfTrueThenJumpElseJumpCommand = 3,
                    IfFalseThenJumpElseJumpCommand = 4,
                    CallCommand = 5,
                    CallNativeCommand = 6,
                    ReturnCommand = 7,
                    YieldCommand = 8,

                    AssignmentOperator = 9,
                    AdditionOperator = 10,
                    EqualityOperator = 11,
                    InequalityOperator = 12,

                    //ConcatenationOperator
                    //AssignmentOperator = 9,
                    //NegationOperator = 10,
                    //AdditionOperator = 11,
                    //SubtractionCommand = 12,
                    //MultiplicationOperator = 13,
                    //DivisionOperator = 14,
                    //ModulusOperator = 15,
                    //SquareBracketsOperator = 17,
                    //LogicalANDOperator = 16,
                    //LogicalOROperator = 17,
                    //LogicalXOROperator = 18,
                    //LogicalLeftShiftOperator = 19,
                    //LogicalRightShiftOperator = 20,
                    //LogicalNegation = 21,
                    //EqualityOperator = 21,
                    //InequalityOperator = 22,
                    //LessThanOperator = 23,
                    //GreaterThanOperator = 24,
                    //LessThanOrEqualOperator = 25,
                    //GreaterThanOrEqualOperator = 26,
                    //ConditionalANDOperator = 27,
                    //ConditionalOROperator = 28,
                    //AdditionAssignmentOperator = 29,
                    //SubtractionAssignmentOperator = 30,
                    //MultiplicationAssignmentOperator = 31,
                    //DivisionAssignmentOperator = 32,
                    //ModulusAssignmentOperator = 33,
                    //LogicalANDAssignmentOperator = 34,
                    //LogicalORAssignmentOperator = 35,
                    //LogicalXORAssignmentOperator = 36,
                    //LogicalLeftShiftAssignmentOperator = 37,
                    //LogicalRightShiftAssignmentOperator = 38,
                };
  
            public:
                ScriptProcess(Script* script);
                virtual ~ScriptProcess();

                void Resume();
                void Suspend();

            private:
                ScriptPtr script;
                uint position;
        };
    }

#   include <Bibim/ScriptProcess.inl>

#endif