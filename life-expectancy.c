#include <stdio.h>
#include <string.h>

void displaySpaces(int spaceCount);
void displayNewLines(int lineCount);
void loadQuestionsAndOptions(char* questionsAndOptions[][2]);
void loadStatistics(char* stats[]);
char readFirstCharacter();

int main() {
   setbuf(stdout, NULL);
   char userResponse;
   int lifeExpectancy = 72;
   char validChoices[15] = "ABCDEMGHIJKLFNO";

   displaySpaces(23);
   printf("LIFE EXPECTANCY\n");
   displaySpaces(22);
   printf("CREATIVE COMPUTING\n");
   displaySpaces(20);
   printf("MORRISTOWN, NEW JERSEY\n");
   displayNewLines(6);
   printf("THIS IS A LIFE EXPECTANCY TEST.\n");
   printf("   DO YOU WISH INSTRUCTIONS? ");
   userResponse = readFirstCharacter();
   if (userResponse != 'N')
   {
      displayNewLines(2);
      printf("   THIS IS A TEST TO PREDICT YOUR LIFE EXPECTANCY.  I\n");
      printf("WILL ASK YOU A SERIES OF SHORT QUESTIONS, WHICH YOU WILL\n");
      printf("REPLY BY TYPING IN THE CORRESPONDING ANSWER TO THE\n");
      printf("QUESTION.\n");
      displayNewLines(1);
      printf("        EXAMPLE:  WHAT IS YOUR SEX?\n");
      printf("               M=MALE\n");
      printf("               F=FEMALE\n");
      printf("'M' AND 'F' ARE THE POSSIBLE REPLIES TO THE QUESTION, ANSWER\n");
      printf("LIKE THIS:\n");
      printf("              CHOOSE ONE OF THE LETTERS ABOVE? M\n");
      printf("TYPING AN 'M' SIGNIFIES YOU ARE A MALE.\n");
      displayNewLines(3);
   }

   char* questionsAndOptions[21][2];
   loadQuestionsAndOptions(questionsAndOptions);
   
   const int QUESTION_COLUMN = 0;
   const int OPTION_COLUMN = 1;
   const int TOTAL_QUESTIONS = 21;
   char questionText[215];
   for (int currentQuestionIndex = 0; currentQuestionIndex < TOTAL_QUESTIONS; currentQuestionIndex++)
   {
      strcpy(questionText, questionsAndOptions[currentQuestionIndex][QUESTION_COLUMN]);
      char* part = strtok(questionText, "|");
      while (part != NULL)
      {
         if (part[0] == ' ')
         {
            printf(" %s\n", part);
         }
         else
         {
            printf("  %s\n", part);
         }
         part = strtok(NULL, "|");
      }
      while (1)
      {
         printf("CHOOSE ONE OF THE LETTERS ABOVE? ");
         userResponse = readFirstCharacter();
         if (strchr(questionsAndOptions[currentQuestionIndex][OPTION_COLUMN], (int)userResponse) != NULL)
         {
            for (int choiceIndex = 0; choiceIndex < sizeof(validChoices); choiceIndex++)
            {
               if (validChoices[choiceIndex] == userResponse)
               {
                  choiceIndex++;
                  lifeExpectancy = lifeExpectancy + (choiceIndex - 9);
                  break;
               }
            }
            displayNewLines(1);
            break;
         }
      }
   }
   printf("YOU ARE EXPECTED TO LIVE TO THE AGE OF %d YEARS", lifeExpectancy);
   if (lifeExpectancy >= 60)
   {
      const int TOTAL_STATISTICS = 16;
      char* stats[TOTAL_STATISTICS];
      char* maleStat;
      char* femaleStat;

      loadStatistics(stats);
      int statIndex = 0;
      for (int year = 60; year < lifeExpectancy; year += 5)
      {
         int nextYear = year + 5;
         if (nextYear > lifeExpectancy)
         {
            break;
         }
         statIndex += 2;
      }
      if (statIndex < (TOTAL_STATISTICS - 1))
      {
         maleStat = stats[statIndex];
         statIndex++;
         femaleStat = stats[statIndex];
         printf("\nOUT LIVING %s OF THE MEN AND %s OF THE WOMEN.", maleStat, femaleStat);
      }
      else
      {
         printf("\n!OUT OF DATA");
      }
   }

   getchar();
   return 0;
}

void displaySpaces(int spaceCount)
{
   for (int i = 0; i < spaceCount; i++)
   {
      printf(" ");
   }
}

void displayNewLines(int lineCount)
{
   for (int i = 0; i < lineCount; i++)
   {
      printf("\n");
   }
}

void loadQuestionsAndOptions(char* questionsAndOptions[][2])
{
   questionsAndOptions[0][0]  = "+++SEX+++|ARE YOU MALE OR FEMALE?|M= MALE.| F= FEMALE.|";
   questionsAndOptions[0][1]  = "MF";

   questionsAndOptions[1][0]  = "+++LIFE STYLE+++|WHERE DO YOU LIVE?|G= IF YOU LIVE IN AN URBAN AREA WITH A POPULATION OVER 2 MIL.|K= IF YOU LIVE IN A TOWN UNDER 10,000, OR ON A FARM.| I= NEITHER.|";
   questionsAndOptions[1][1]  = "GKI";

   questionsAndOptions[2][0]  = "HOW DO YOU WORK?|M= IF YOU WORK BEHIND A DESK.|L= IF YOUR WORK REQUIRES HEAVY PHYSICAL LABOR.| I= NONE OF THE ABOVE.|";
   questionsAndOptions[2][1]  = "MLI";

   questionsAndOptions[3][0]  = "HOW LONG DO YOU EXERCISE STRENUOUSLY,|(TENNIS, RUNNING, SWIMMING, ETC.)?|F= FIVE TIMES A WEEK FOR AT LEAST A HALF HOUR.|K= JUST TWO OR THREE TIMES A WEEK.| I= DO NOT EXERCISE IN THIS FASHION.|";
   questionsAndOptions[3][1]  = "FKI";
   
   questionsAndOptions[4][0]  = "WHO DO YOU LIVE WITH?|N= IF YOU LIVE WITH A SPOUSE, FRIEND, OR IN A FAMILY.|H= IF YOU'VE LIVED ALONE FOR 1-10 YEARS SINCE AGE 25.|G= FOR 11-20 YEARS.|M= FOR 21-30 YEARS.|E= FOR 31-40 YEARS.| D= MORE THAN 40 YEARS.|";
   questionsAndOptions[4][1]  = "NHGMED";

   questionsAndOptions[5][0]  = "DO YOU SLEEP MORE THAN 10 HOURS A NIGHT?|I= NO.| E= YES.|";
   questionsAndOptions[5][1]  = "IE";

   questionsAndOptions[6][0]  = "+++MENTAL STATE+++|M= IF YOU ARE INTENSE, AGGRESSIVE, OR EASILY ANGERED.|L= IF YOU ARE EASY GOING, RELAXED, OR A FOLLOWER.| I= NEITHER.|";
   questionsAndOptions[6][1]  = "MLI";

   questionsAndOptions[7][0]  = "+++HOW YOU FEEL+++|ARE YOU HAPPY OR UNHAPPY?|J= HAPPY.|G= UNHAPPY.| I= NEITHER.|";
   questionsAndOptions[7][1]  = "JGI";

   questionsAndOptions[8][0]  = "+++FACTORS+++|HAVE YOU HAD A SPEEDING TICKET IN THE LAST YEAR?|H= YES.| I=NO.|";
   questionsAndOptions[8][1]  = "HI";

   questionsAndOptions[9][0]  = "+++INCOME+++|DO YOU EARN MORE THAN $50,000 A YEAR?|G= YES.| I=NO.|";
   questionsAndOptions[9][1]  = "GI";

   questionsAndOptions[10][0] = "+++SCHOOLING+++|J= IF YOU HAVE FINISHED COLLEGE.|L= IF YOU HAVE FINISHED COLLEGE WITH A GRADUATE|OR PROFESSIONAL DEGREE.| I= NOTHING LISTED.|";
   questionsAndOptions[10][1]  = "JLI";

   questionsAndOptions[11][0] = "+++AGE+++|ARE YOU 65 OR OLDER AND STILL WORKING?|L= YES.| I= NO.|";
   questionsAndOptions[11][1]  = "LI";

   questionsAndOptions[12][0] = "+++HEREDITY+++|K= IF ANY GRANDPARENTS LIVED TO 85 YEARS OLD.|O= IF ALL FOUR GRANDPARENTS LIVED TO 80 YEARS OLD.| I= NO GRANDPARENTS QUALIFY IN THE ABOVE.|";
   questionsAndOptions[12][1]  = "KOI";

   questionsAndOptions[13][0] = "HAS ANY PARENT DIED OF A STROKE OR HEART ATTACK|BEFORE THE AGE OF 50?|E= YES.| I= NO.|";
   questionsAndOptions[13][1]  = "EI";

   questionsAndOptions[14][0] = "+++FAMILY DISEASES+++|ANY PARENT, BROTHER, OR SISTER UNDER 50 HAS (OR HAD) |CANCER, A HEART CONDITION, OR DIABETES SINCE CHILDHOOD?|M= YES.| I= NO.|";

   questionsAndOptions[14][1]  = "MI";

   questionsAndOptions[15][0] = "+++HEALTH+++|HOW MUCH DO YOU SMOKE?|A= IF YOU SMOKE MORE THAN TWO PACKS A DAY.|C= ONE TO TWO PACKS A DAY.|M= ONE HALF TO ONE PACK A DAY.| I= DON'T SMOKE.|";
   questionsAndOptions[15][1]  = "ACMI";

   questionsAndOptions[16][0] = "+++DRINK+++|DO YOU DRINK THE EQUIVALENT OF A |QUARTER BOTTLE OF ALCOHOLIC BEVERAGE A DAY?|H= YES.| I= NO.|";
   questionsAndOptions[16][1]  = "HI";

   questionsAndOptions[17][0] = "+++WEIGHT+++|A= IF YOU ARE OVERWEIGHT BY 50 POUNDS OR MORE.|E= OVER BY 30-50 POUNDS.|G= OVER BY 10-30 POUNDS.| I= NOT OVER WEIGHT.|";
   questionsAndOptions[17][1]  = "AEGI";

   questionsAndOptions[18][0] = "+++CHECKUPS+++|DO YOU?  IF YOU ARE A MALE OVER 40 HAVE AN ANNUAL CHECKUP?|K= YES.| I= IF NO OR NOT A MALE OR UNDER 40 YEARS OLD.|";
   questionsAndOptions[18][1]  = "KI";

   questionsAndOptions[19][0] = "DO YOU? IF YOU ARE A WOMAN SEE A GYNECOLOGIST ONCE A YEAR?|K= YES.| I= IF NO OR NOT A WOMAN.|";
   questionsAndOptions[19][1]  = "KI";

   questionsAndOptions[20][0] = "+++CURRENT AGE+++|K= IF YOU ARE BETWEEN 30 AND 40 YEARS OLD.|L= BETWEEN 40 AND 50.|F= BETWEEN 50 AND 70.|N= OVER 70.| I= UNDER 30.|";
   questionsAndOptions[20][1]  = "KLFNI";
}

void loadStatistics(char* stats[])
{
   stats[0]  = "26%";
   stats[1]  = "15%";
   stats[2]  = "36%";
   stats[3]  = "20%";
   stats[4]  = "48%";
   stats[5]  = "30%";
   stats[6]  = "61%";
   stats[7]  = "39%";
   stats[8]  = "75%";
   stats[9]  = "53%";
   stats[10] = "87%";
   stats[11] = "70%";
   stats[12] = "96%";
   stats[13] = "88%";
   stats[14] = "99.9%";
   stats[15] = "99.6%";   
}

char readFirstCharacter()
{
   int nextChar;
   char firstChar;
   scanf(" %c", &firstChar);
   while((nextChar = getchar()) != '\n');
   return firstChar;
}
