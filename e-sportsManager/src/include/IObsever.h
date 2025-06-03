/*************
 * 观察者接口 *
 *************/

class IObserver {
    public:
        virtual ~IObserver() = default;
        
        // 更新
        virtual void update() = 0;
};