#pragma once
#ifndef __BIBIM_EVALBOARD_H__
#define __BIBIM_EVALBOARD_H__

#   include <Bibim/FWD.h>
#   include <Bibim/GameAsset.h>
#   include <Bibim/Evals.h>
#   include <Bibim/String.h>
#   include <vector>

    namespace Bibim
    {
        class EvalBoard : public GameAsset
        {
            BBSerializableAssetClass(EvalBoard, GameAsset, 'e', 'b', 'o', 'd');
            public:
                struct Item
                {
                    String Name;
                    EvalBasePtr Root;
                };
                typedef std::vector<Item> ItemCollection;

            public:
                EvalBoard();
                virtual ~EvalBoard();

                EvalBase* Find(const String& name) const;
                inline float GetDuration() const;
                inline const ItemCollection& GetItems() const;

            private:
                EvalBoard(float duration, std::vector<Item>& items);

            private:
                float duration;
                ItemCollection items;
        };
    }

#   include <Bibim/EvalBoard.inl>

#endif