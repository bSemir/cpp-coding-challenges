// TP 2023/2024: Zadaća 4, Zadatak 1
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <vector>

typedef std::pair<double, double> Tacka;
enum Pozicija { GoreLijevo, GoreDesno, DoljeLijevo, DoljeDesno };
enum Smjer { Nalijevo, Nadesno };

class Pravougaonik {
private:
    Tacka t1, t2;

public:
    Pravougaonik(const Tacka &t1, const Tacka &t2) { Postavi(t1, t2); }
    void Postavi(const Tacka &t1, const Tacka &t2) {
        this->t1 = t1;
        this->t2 = t2;
    }
    void Postavi(Pozicija p, const Tacka &t) {
        switch (p) {
            case GoreLijevo:
                t1 = t;
                break;
            case GoreDesno:
                t2.first = t.first - (t2.first - t1.first);
                t1.second = t.second;
                break;

            case DoljeLijevo:
                t1.first = t.first;
                t2.second = t.second;
            case DoljeDesno:
                t2 = t;
                break;
        }
        // switch (p) {
        // case GoreLijevo:
        //   if (t.first < t2.first && t.second > t2.second) {
        //     std::swap(t1, t2);
        //   } else if (t.first > t2.first && t.second < t2.second) {
        //     std::swap(t1.first, t2.first);
        //   } else if (t.first < t2.first) {
        //     std::swap(t1.first, t2.first);
        //     std::swap(t1.second, t2.second);
        //   } else {
        //     std::swap(t1, t2);
        //   }
        //   break;
        // case GoreDesno:
        //   if (t.first > t1.first && t.second > t2.second) {
        //     std::swap(t1, t2);
        //   } else if (t.first < t1.first && t.second < t2.second) {
        //     std::swap(t1.first, t2.first);
        //   } else if (t.first > t1.first) {
        //     std::swap(t1.first, t2.first);
        //     std::swap(t1.second, t2.second);
        //   }
        //   break;
        // case DoljeLijevo:
        //   if (t.first < t2.first && t.second < t1.second) {
        //     std::swap(t1, t2);
        //   } else if (t.first > t2.first && t.second > t1.second) {
        //     std::swap(t1.first, t2.first);
        //   } else if (t.first < t2.first) {
        //     std::swap(t1.first, t2.first);
        //     std::swap(t1.second, t2.second);
        //   } else {
        //     std::swap(t1, t2);
        //   }
        //   break;
        // case DoljeDesno:
        //   if (t.first > t1.first && t.second < t1.second) {
        //     std::swap(t1, t2);
        //   } else if (t.first < t1.first && t.second > t1.second) {
        //     std::swap(t1.first, t2.first);
        //   } else if (t.first > t1.first) {
        //     std::swap(t1.first, t2.first);
        //     std::swap(t1.second, t2.second);
        //   }
        //   break;
        // }

        if (t1.first != t2.first && t1.second != t2.second) {
            if (t1.first > t2.first && t1.second > t2.second) {
                std::swap(t1, t2);
            } else if (t1.first > t2.first) {
                std::swap(t1.first, t2.first);
            } else if (t1.second > t2.second) {
                std::swap(t1.second, t2.second);
            }
        }
    }

    Tacka DajCentar() const {
        return {(t1.first + t2.first) / 2, (t1.second + t2.second) / 2};
    }
    void Centriraj(const Tacka &t) {
        Tacka centar = DajCentar();
        double delta_x = t.first - centar.first;
        double delta_y = t.second - centar.second;
        Transliraj(delta_x, delta_y);
    }
    Tacka DajTjeme(Pozicija p) const {
        switch (p) {
            case GoreLijevo:
                return {std::min(t1.first, t2.first), std::max(t1.second, t2.second)};
            case GoreDesno:
                return {std::max(t1.first, t2.first), std::max(t1.second, t2.second)};
            case DoljeLijevo:
                return {std::min(t1.first, t2.first), std::min(t1.second, t2.second)};
            case DoljeDesno:
                return {std::max(t1.first, t2.first), std::min(t1.second, t2.second)};
        }
        return {0, 0};
    }
    double DajVertikalnu() const { return std::abs(t1.second - t2.second); }
    double DajHorizontalnu() const { return std::abs(t1.first - t2.first); }
    double DajObim() const { return 2 * (DajHorizontalnu() + DajVertikalnu()); }
    double DajPovrsinu() const { return DajHorizontalnu() * DajVertikalnu(); }
    static Pravougaonik Presjek(const Pravougaonik &p1, const Pravougaonik &p2) {
        double x_min = std::max(p1.t1.first, p2.t1.first);
        double y_min = std::max(p1.t1.second, p2.t1.second);
        double x_max = std::min(p1.t2.first, p2.t2.first);
        double y_max = std::min(p1.t2.second, p2.t2.second);

        if (x_min > x_max || y_min > y_max)
            throw std::domain_error("Pravougaonici se ne presjecaju");

        return Pravougaonik({x_min, y_min}, {x_max, x_min});
    }
    void Transliraj(double delta_x, double delta_y) {
        t1.first += delta_x;
        t1.second += delta_y;
        t2.first += delta_x;
        t2.second += delta_y;
    }

    void Rotiraj(const Tacka &t, Smjer s) {
        auto rotiraj_t = [&t](Tacka &tacka, Smjer s) {
            double x_new, y_new;
            if (s == Nalijevo) {
                x_new = t.first - (tacka.second - t.second);
                y_new = t.second + (tacka.first - t.first);
            } else {
                x_new = t.first + (tacka.second - t.second);
                y_new = t.second - (tacka.first - t.first);
            }
            tacka = {x_new, y_new};
        };
        rotiraj_t(t1, s);
        rotiraj_t(t2, s);
    }

    void Ispisi() const {
        Tacka gore_lijevo = DajTjeme(GoreLijevo);
        Tacka dolje_desno = DajTjeme(DoljeDesno);
        std::cout << "{{" << gore_lijevo.first << "," << gore_lijevo.second << "},"
                  << "{" << dolje_desno.first << "," << dolje_desno.second << "}}";
    }

    friend bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2);

    friend bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2);

    friend bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2);
};

bool DaLiSePoklapaju(const Pravougaonik &p1, const Pravougaonik &p2) {
    auto t1_p1 = p1.DajTjeme(GoreLijevo);
    auto t1_p2 = p2.DajTjeme(GoreLijevo);
    auto t2_p1 = p1.DajTjeme(DoljeDesno);
    auto t2_p2 = p2.DajTjeme(DoljeDesno);

    return t1_p1 == t1_p2 && t2_p1 == t2_p2;
}

bool DaLiSuPodudarni(const Pravougaonik &p1, const Pravougaonik &p2) {
    return (p1.DajHorizontalnu() == p2.DajHorizontalnu() &&
            p1.DajVertikalnu() == p2.DajVertikalnu() ||
            (p1.DajHorizontalnu() == p2.DajVertikalnu() &&
             p1.DajVertikalnu() == p2.DajHorizontalnu()));
}

bool DaLiSuSlicni(const Pravougaonik &p1, const Pravougaonik &p2) {
    double om1 = p1.DajHorizontalnu() / p1.DajVertikalnu();
    double om2 = p2.DajHorizontalnu() / p2.DajVertikalnu();
    // const double tol = 1e-6;
    //   return (om1 == om2) || (om1 == (1 / om2));
    return std::abs(om1 - om2) < 1e-6;
    // bool slicni =
    //     (std::abs(om1 - om2) < tol || std::abs(om1 - (1 / om2)) < tol);

    // bool ista_orijentacija = (p1.DajHorizontalnu() > p1.DajVertikalnu() &&
    //                           p2.DajHorizontalnu() > p2.DajVertikalnu()) ||
    //                          (p1.DajHorizontalnu() < p1.DajVertikalnu() &&
    //                           p2.DajHorizontalnu() < p2.DajVertikalnu());

    // return slicni && ista_orijentacija;
}
int main() {
    int n;
    std::cout << "Unesite n: ";
    std::cin >> n;

    std::vector<Pravougaonik *> pravougaonici(n);

    for (int i = 0; i < n; i++) {
        double x1, y1, x2, y2;
        std::cout << "Unesite 1. tjeme pravougaonika " << i + 1 << ": ";
        std::cin >> x1 >> y1;
        std::cout << "Unesite 2. tjeme pravougaonika " << i + 1 << ": ";
        std::cin >> x2 >> y2;
        pravougaonici[i] = new Pravougaonik(Tacka{x1, y1}, Tacka{x2, y2});
    }

    // podaci za transliranje
    double delta_x, delta_y;
    std::cout << "Unesite podatke za transliranje (dx dy): ";
    std::cin >> delta_x >> delta_y;

    // translacija
    std::for_each(
            pravougaonici.begin(), pravougaonici.end(),
            [delta_x, delta_y](Pravougaonik *p) { p->Transliraj(delta_x, delta_y); });

    // rotacija oko centra
    std::for_each(pravougaonici.begin(), pravougaonici.end(),
                  [](Pravougaonik *p) { p->Rotiraj(p->DajCentar(), Nalijevo); });

    // ispis nakon transf
    std::cout << "Pravougaonici, nakon transformacija:\n";
    std::for_each(pravougaonici.begin(), pravougaonici.end(),
                  [](Pravougaonik *p) {
                      p->Ispisi();
                      std::cout << "\n";
                  });

    // pravougaonik s najvecom povrsinom
    auto max_povrsina =
            *std::max_element(pravougaonici.begin(), pravougaonici.end(),
                              [](Pravougaonik *p1, Pravougaonik *p2) {
                                  return p1->DajPovrsinu() < p2->DajPovrsinu();
                              });

    std::cout << "Pravougaonik s najvecom povrsinom: ";
    (*max_povrsina).Ispisi();
    std::cout << "\n";

    for (auto &p : pravougaonici)
        delete p;
    // delete[] pravougaonici;

    return 0;
}