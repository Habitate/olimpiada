#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct State{
    State(const int cleaned, const int painted) : cleaned(cleaned), painted(painted), just_cleaned(false){}

    int cleaned;
    int painted;

    bool just_cleaned;
};

int main(){
    int count, clean_time, paint_time, delay, free_time(0), tomas_pos(0), barbora_pos(0);
    cin >> count >> clean_time >> paint_time >> delay;

    vector<State> tvora(count, State{clean_time, paint_time});

    while(true){
        for_each(begin(tvora), end(tvora), [](State& state){ state.just_cleaned = false; });

        if(tomas_pos != count){
            if(tvora[tomas_pos].cleaned != 0){
                --tvora[tomas_pos].cleaned;
            }
            if(tvora[tomas_pos].cleaned == 0){
                tvora[tomas_pos].just_cleaned = true;
                ++tomas_pos;
            }
        }

        if(barbora_pos == count){
            break;
        }
        if(delay){
            --delay;
            continue;
        }

        if(tvora[barbora_pos].cleaned == 0 && tvora[barbora_pos].just_cleaned == false){
            if(tvora[barbora_pos].painted != 0){
                --tvora[barbora_pos].painted;
            }
            if(tvora[barbora_pos].painted == 0){
                ++barbora_pos;
            }
        }
        else{
            ++free_time;
        }
    }

    cout << free_time;

    return 0;
}