{


  double Energy;

TF1 *f2 = new TF1("f2","exp(pow(pow([0]+[1]*log(x/[7])+[2]*log(x/[7])*log(x/[7]),-[6])+pow([3]+[4]*log(x/[8])+[5]*log(x/[8])*log(x/[8]),-[6]),-1/[6]))",38.5,2500);

f2->SetParameter(0,10.8);
f2->SetParameter(1,6.964);
f2->SetParameter(2,-2.553);
f2->SetParameter(3,2.981);
f2->SetParameter(4,-0.6119);
f2->SetParameter(5,0.1342);
f2->SetParameter(6,0.7077);
f2->SetParameter(7,100);
f2->SetParameter(8,1000);


 cin>>Energy;

cout << f2->Eval(Energy) << endl; 


}

