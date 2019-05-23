#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include <string>

namespace Mysystem
{
	template <class Key>
	class SceneMaster
	{
	public:

		using KeyType = Key;

	public:

		class SceneBase
		{
		private:

			SceneMaster<Key>* master;

		protected:

			virtual void changeScene(const Key& next) final
			{
				master->changeScene(next);
			}

		public:

			virtual void setdata(SceneMaster<Key>* _master) final
			{
				master = _master;
			}

			virtual void update() {}
			virtual void draw() const {}
			virtual ~SceneBase() {}
		};

	private:

		std::shared_ptr<SceneBase> currentscene;

		std::unordered_map<Key, std::function<std::shared_ptr<SceneBase>()>> scenelist;

		bool changereserve;

		Key nextscenename;

	public:

		template <class SceneType>
		void Add(const Key& key)
		{
			auto factory = [=]() {
				auto val = std::make_shared<SceneType>();
				val->setdata(this);
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
		{}
	};
}