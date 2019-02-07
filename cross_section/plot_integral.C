{
  Double_t x, y, z;
  Double_t s[1000], realpart[1000], imagpart[1000];
  ifstream input("integral.txt");
  if (!input) {
    cout << "could not open file\n";
    return 1;
  } else {
    cout << "file found\n";
  }
  int n = 0;
  while (input >> x >> y >> z) {
    cout << n << ' ' << x << ' ' << y << ' ' << z << endl;
    s[n] = x;
    realpart[n] = y;
    imagpart[n] = z;
    n++;
  }

  cout << s[0] << endl;
  Int_t np = 93;
  TGraph *grr = new TGraph(np, s, realpart);
  TGraph *gri = new TGraph(np, s, imagpart);
  gri->SetLineColor(2);
  TMultiGraph *mg = new TMultiGraph();
  mg->Add(grr);
  mg->Add(gri);
  TCanvas *c1 = new TCanvas("c1","Graph Draw Options",
                             200,10,600,400);
  //TAxis *axis = grr->GetYaxis();
  //axis->SetLimits(-15.,5.);
  //grr->Draw("AC");
  //gri->Draw("AC");
  mg->Draw("ALP");
  gPad->SetGrid();
  gPad->Update();
}
