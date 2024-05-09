/*
   Copyright 2021 FogML

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

int classifier(float * x){
  int results[11];
  if (x[11] <= 7.0000000000) {
    if (x[2] <= 1.3211399913) {
      results[0] = 0;
    }
    else {
      results[0] = 1;
    }
  }
  else {
    if (x[5] <= 0.9938429892) {
      results[0] = 2;
    }
    else {
      results[0] = 0;
    }
  }
  if (x[5] <= 0.8346534967) {
    results[1] = 0;
  }
  else {
    if (x[10] <= 7.0000000000) {
      if (x[1] <= 0.0756962989) {
        results[1] = 1;
      }
      else {
        results[1] = 0;
      }
    }
    else {
      results[1] = 2;
    }
  }
  if (x[7] <= 3.1351799965) {
    results[2] = 0;
  }
  else {
    if (x[2] <= 2.7805000544) {
      results[2] = 1;
    }
    else {
      results[2] = 2;
    }
  }
  if (x[5] <= 0.8995479941) {
    if (x[5] <= 0.8463280201) {
      results[3] = 0;
    }
    else {
      if (x[6] <= 1.1665550470) {
        results[3] = 2;
      }
      else {
        results[3] = 0;
      }
    }
  }
  else {
    if (x[0] <= 0.5477800071) {
      if (x[8] <= 3.6679499149) {
        results[3] = 2;
      }
      else {
        results[3] = 1;
      }
    }
    else {
      if (x[10] <= 6.5000000000) {
        results[3] = 1;
      }
      else {
        results[3] = 2;
      }
    }
  }
  if (x[10] <= 6.5000000000) {
    if (x[2] <= 1.1951149702) {
      results[4] = 0;
    }
    else {
      if (x[2] <= 2.9356850386) {
        results[4] = 1;
      }
      else {
        results[4] = 2;
      }
    }
  }
  else {
    if (x[3] <= -0.3542785048) {
      results[4] = 0;
    }
    else {
      results[4] = 2;
    }
  }
  if (x[7] <= 11.1864852905) {
    if (x[1] <= 0.0756962989) {
      if (x[8] <= 3.0595099330) {
        results[5] = 0;
      }
      else {
        results[5] = 1;
      }
    }
    else {
      results[5] = 0;
    }
  }
  else {
    results[5] = 2;
  }
  if (x[2] <= 1.2053599954) {
    results[6] = 0;
  }
  else {
    if (x[7] <= 11.3872551918) {
      if (x[0] <= 1.0556659698) {
        results[6] = 1;
      }
      else {
        results[6] = 0;
      }
    }
    else {
      results[6] = 2;
    }
  }
  if (x[4] <= 1.5979549885) {
    if (x[9] <= 2.5000000000) {
      results[7] = 0;
    }
    else {
      if (x[10] <= 7.0000000000) {
        results[7] = 0;
      }
      else {
        results[7] = 2;
      }
    }
  }
  else {
    if (x[2] <= 1.2053599954) {
      results[7] = 0;
    }
    else {
      if (x[3] <= -0.3553294986) {
        results[7] = 0;
      }
      else {
        results[7] = 1;
      }
    }
  }
  if (x[7] <= 3.3343650103) {
    results[8] = 0;
  }
  else {
    if (x[7] <= 11.6451501846) {
      results[8] = 1;
    }
    else {
      results[8] = 2;
    }
  }
  if (x[0] <= 0.4964180142) {
    if (x[7] <= 2.4084699750) {
      results[9] = 0;
    }
    else {
      if (x[4] <= 1.1863300204) {
        results[9] = 2;
      }
      else {
        results[9] = 1;
      }
    }
  }
  else {
    if (x[11] <= 7.5000000000) {
      results[9] = 0;
    }
    else {
      if (x[8] <= 0.9317220151) {
        results[9] = 0;
      }
      else {
        results[9] = 2;
      }
    }
  }
  if (x[7] <= 3.0487350225) {
    results[10] = 0;
  }
  else {
    if (x[7] <= 12.7327203751) {
      results[10] = 1;
    }
    else {
      results[10] = 2;
    }
  }
  int classes_amount = 0;
  for(int i=0; i<11; i++){
  	if(results[i]+1 > classes_amount) classes_amount = results[i]+1;  }
  int result_class = -1;
  int max_apperance = 0;
  for(int i=0; i<classes_amount; i++){
   int apperance = 0;
  	for(int j=0; j<11; j++) if(results[j] == i) apperance++;
  	if(apperance > max_apperance){
  		max_apperance = apperance;
  		result_class = i;
  	}
  }
  return result_class;
}
