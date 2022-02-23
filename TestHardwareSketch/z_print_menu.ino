void PrintMenu(void)
{
  char printArray [1000];
  sprintf(printArray, "a = test IR LED\nb = test switches\nc = test buttons\ne = test motor and sensor\nd = test motor\nf = test motor and encoder\nz = print menu\n\n");
  Serial.print(printArray);
  //  Serial.println("a = test IR LED");
  //  Serial.println("b = test switches");
  //  Serial.println("c = test buttons");
  //  Serial.println("z = print menu");
  //  Serial.println();
}
