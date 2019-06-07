#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include <string>

namespace Mysystem
{
    template <class Key, class Common>
    class SceneMaster
    {
    public:

        using KeyType = Key;

    public:

        // <SceneBase>

        class SceneBase
        {
        private:

            SceneMaster<Key, Common>& master;

        protected:

            virtual void changeScene(const Key& next) final
            {
                master.changeScene(next);
            }

            inline Common& getCommon()
            {
                return master.GetCommonData();
            }

        public:

            SceneBase(SceneMaster<Key, Common>& _master)
                : master(_master)
            {}

            virtual void update() {}
            virtual void draw() const {}
            virtual ~SceneBase() {}
        };

        // </SceneBase>

    private:

        std::shared_ptr< Common > commondata;

        std::shared_ptr<SceneBase> currentscene;

        std::unordered_map<Key, std::function<std::shared_ptr<SceneBase>()>> scenelist;

        bool changereserve;

        Key nextscenename;

    public: //プロパティ

        inline Common GetCommonData()
        {
            return commondata;
        }

    public:

        template <class SceneType>
        /// <summary>
        /// シーンの追加
        /// </summary>
        /// <param name="key">シーン指定方法</param>
        void Add(const Key& key)
        {
            auto factory = [=]() {
                auto val = std::make_shared<SceneType>(*this);
                return val;
            };

            auto it = scenelist.find(key);

            if (it == scenelist.end())
            {
                scenelist.emplace(key, factory);

                if (!currentscene)
                {
                    currentscene = scenelist[key]();
                }
            }
            else
            {
                scenelist[key] = factory;
            }
        }

        bool changeScene(const Key& next)
        {
            auto it = scenelist.find(next);

            if (it == scenelist.end())
            {
                return false;
            }

            changereserve = true;
            nextscenename = next;
            return true;
        }

        void Update()
        {
            if (changereserve)
            {
                changereserve = false;
                currentscene = scenelist[nextscenename]();
            }

            if (!currentscene)
            {
                return;
            }

            currentscene->update();
        }

        void Draw() const
        {
            if (!currentscene)
            {
                return;
            }

            currentscene->draw();
        }

        SceneMaster()
            : changereserve(false)
            , scenelist()
        {
            commondata = std::make_shared<Common>();
        }
    };
}