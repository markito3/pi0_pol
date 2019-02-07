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
  TGraph *grr = new TGraph(np, s, realpart); // number of points, x array, y array
  TGraph *gri = new TGraph(np, s, imagpart);
  gri->SetLineColor(kRed);
  TMultiGraph *mg = new TMultiGraph(); // graph container class
  mg->Add(grr);
  mg->Add(gri);
  TCanvas *c1 = new TCanvas("c1","G_pi",200,10,600,400);
  mg->Draw("ALP");
  gPad->SetGrid();
  TLegend *legend = new TLegend(0.7,0.7,0.9,0.8); // lower left x, y, upper right x, y
  legend->AddEntry(grr,"real part","l");
  legend->AddEntry(gri,"imaginary part","l");
  legend->Draw();
  //TAxis *x_axis, *y_axis;
  mg->GetXaxis()->SetTitle("s (GeV^{2})");
  mg->GetXaxis()->SetTitleSize(0.05);
  mg->GetYaxis()->SetTitle("G_{#pi}(s)");
  mg->GetYaxis()->SetTitleSize(0.05);
  gPad->Modified();
}
