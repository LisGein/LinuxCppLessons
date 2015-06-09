import math

def calc_betta(specific_gas_const, k, Tk):
    A = math.sqrt(2 / (k + 1)) * (2 / (k + 1)) ** (1 / (k - 1))
    betta = math.sqrt(specific_gas_const * Tk) / A
    return betta

def calc_gdf_Tau(lambda_, k):
    return (1 - (k - 1) / (k + 1) * lambda_ ** 2)

def calc_gdf_pi(lambda_, k):
    gdf_pi = (1 - (k - 1) / (k + 1) * lambda_ ** 2) ** (k / (k - 1))
    return gdf_pi

def calc_gdf_esp(lambda_, k):
    gdf_eps = (1 - (k - 1) / (k + 1) * lambda_ ** 2) ** (1 / (k - 1))
    return gdf_eps

def calc_gdf_qu(lambda_, k):
    gdf_qu = ((k + 1) / 2) ** (1 / (k - 1)) * lambda_ * calc_gdf_esp(lambda_, k)
    return gdf_qu

def calc_Fkr(rho, Sg0, u1, betta, P0, Pk, nu):
    u = u1 * (Pk / P0) ** nu
    Fkr = (rho * Sg0 * u * betta) / Pk
    return Fkr

def calc_cilindr(D2, D_max, L):
    if D2 >= D_max or L < 0:
        cilindr = 0.000001
    else:
        cilindr = 3.1415926 * D2 * L
    return cilindr

def calc_kolco(D_out, D_in, D_max):
    return math.pi / 4 * (min(D_out, D_max) ** 2 - min(D_in, D_max) ** 2)

def calc_bari(rho, Sg, u1, betta, Fkr, P0, nu):
    Pk = ((rho * Sg * u1 * betta) / (Fkr * P0 ** nu)) ** (1 / (1 - nu))
    return Pk

class CalcCourseWork:

    def __init__(self):
        self.speed_burn = 2
        self.idx_speed_burn = 0.001
        self.burning_rate = 0.2
        self.idx_burning_rate = 1
        self.base_pressure = 100000
        self.idx_base_pressure = 1
        self.ind_isentrope = 1.2
        self.idx_ind_isentrope = 1
        self.estimated_pressure_cc = 14
        self.idx_estimated_pressure_cc = 1000000
        self.estimated_pressure_ne = 20
        self.idx_estimated_pressure_ne = 1000
        self.temp_cc = 3100
        self.idx_temp_cc = 1
        self.molar_mass_ps = 35
        self.idx_molar_mass_ps = 1
        self.fuel_density = 1600
        self.idx_fuel_density = 1
        self.time_step = 0.12
        self.idx_time_step = 1
        self.lambda_ = 2.70341305125348
        self.l1 = 1.5  # length parameter
        self.idx_l1 = 1
        self.l2 = 1  # length parameter
        self.idx_l2 = 1
        self.d1 = 0.5  # diam parameter
        self.idx_d1 = 1
        self.d2 = 0.25  # diam parameter
        self.idx_d2 = 1
        self.d3 = 0.3  # diam parameter
        self.idx_d3 = 1
        self.PI = 3.1415
        self.Fa = 0.0734624980076733
        self.t = []
        self.agle1 = 50
        self.agle2 = 20

    def calc_data(self):
        self.u = self.speed_burn * self.idx_speed_burn
        self.nu = self.burning_rate * self.idx_burning_rate
        self.P0 = self.base_pressure * self.idx_base_pressure
        self.k = self.ind_isentrope * self.idx_ind_isentrope
        self.P_k = self.estimated_pressure_cc * self.idx_estimated_pressure_cc
        self.Pa = self.estimated_pressure_ne * self.idx_estimated_pressure_ne
        self.Tk = self.temp_cc * self.idx_temp_cc
        self.mu = self.molar_mass_ps * self.idx_molar_mass_ps
        self.specific_gas_const = (8314.0 / self.mu)
        self.rho = self.fuel_density * self.idx_fuel_density
        self.h = self.time_step * self.idx_time_step
        self.betta = calc_betta(self.specific_gas_const, self.k, self.Tk)
        self.Akr = math.sqrt(2 * self.k / (self.k + 1) * self.specific_gas_const * self.Tk)
        self.gdf_pi = calc_gdf_pi(self.lambda_, self.k)
        self.gdf_eps = calc_gdf_esp(self.lambda_, self.k)
        self.gdf_qu = calc_gdf_qu(self.lambda_, self.k)
        self.va = self.Akr * self.lambda_
        self.L10_ = self.l1 * self.idx_l1
        self.L20_ = self.l2 * self.idx_l2
        self.D10_ = self.d1 * self.idx_d1
        self.D20_ = self.d2 * self.idx_d2
        self.D30_ = self.d3 * self.idx_d3
        self.L30 = self.L10_ - self.L20_
        self.s10 = calc_cilindr(self.D20_, self.D10_, self.L20_)
        self.s20 = calc_kolco(self.D10_, self.D20_, self.D10_)
        self.s30 = calc_cilindr(self.D30_, self.D10_, self.L30)
        self.s40 = calc_kolco(self.D10_, self.D30_, self.D10_)
        self.Sg0 = self.s10 + self.s20 + self.s30 + self.s40
        self.Fkr = calc_Fkr(self.rho, self.Sg0, self.u, self.betta, self.P0, self.P_k, self.nu)
        self.Dkr = math.sqrt(self.Fkr * 4 / self.PI)
        self.Da = math.sqrt(self.Fa * 4 / self.PI)
        x_t = 0
        x_li = 0

        self.li = []
        self.D20 = []
        self.D30 = []
        self.L10 = []
        self.L20 = []
        self.L30 = []
        self.S10_ = []
        self.S20_ = []
        self.S30_ = []
        self.S40_ = []
        self.Sg = []
        self.pk = []
        self.Gc = []
        self.pa = []
        self.u_Pk = []
        self.P = []
        self.I_spec = []
        for i in range(201):
            self.t.append(x_t)
            x_t = x_t + self.h
            self.li.append(x_li)
            x_d20 = self.D20_ + 2 * self.li[i]
            self.D20.append(x_d20)
            x_d30 = self.D30_ + 2 * self.li[i]
            self.D30.append(x_d30)
            x_l10 = self.L10_ - self.li[i]
            self.L10.append(x_l10)
            x_l20 = self.L20_ - self.li[i]
            self.L20.append(x_l20)
            self.L30.append(self.L10[i] - self.L20[i])
            x_s10 = calc_cilindr(self.D20[i], self.D10_, self.L20[i])
            self.S10_.append(x_s10)
            x_s20 = calc_kolco(self.D10_, self.D20[i], self.D10_)
            self.S20_.append(x_s20)
            x_s30 = calc_cilindr(self.D30[i], self.D10_, self.L30[i])
            self.S30_.append(x_s30)
            x_s40 = calc_kolco(self.D10_, self.D30[i], self.D10_)
            self.S40_.append(x_s40)
            self.Sg.append(self.S10_[i] + self.S20_[i] + self.S30_[i] + self.S40_[i])
            x_pk = calc_bari(self.rho, self.Sg[i], self.u, self.betta, self.Fkr, self.P0, self.nu)
            self.pk.append(x_pk)
            x_Gc = self.pk[i] * self.Fkr / self.betta
            self.Gc.append(x_Gc)
            x_pa = self.pk[i] * self.gdf_pi
            self.pa.append(x_pa)
            x_uPk = self.u * (self.pk[i] / self.P0) ** self.nu
            self.u_Pk.append(x_uPk)
            x_li = x_li + self.u_Pk[i] * self.h
            x_p = self.va * self.Gc[i] + self.Fa * (self.pa[i] - self.Pa)
            self.P.append(x_p)
            if self.Gc[i] > 0.001:
                x_I_spes = self.P[i] / self.Gc[i]
            else:
                x_I_spes = 0
            self.I_spec.append(x_I_spes)


        self.phi1 = math.radians(self.agle1)
        self.phi2 = math.radians(self.agle2)
        self.Fkr_Fa = self.Fkr/self.Fa
        self.lambda_max = math.sqrt((self.k+1)/(self.k-1))
        self.diff1 = self.gdf_pi-self.Pa/self.P_k
        self.diff2 = self.gdf_qu - self.Fkr_Fa
        self.L_bpn = (self.D10_ - self.Dkr)/(2*math.tan(self.phi1))
        self.L_apn = (self.Da - self.Dkr)/(2*math.tan(self.phi2))
        self.Fkr_Fa = self.Fkr/self.Fa
        self.X_bpn = self.L_bpn/5
        X_apn = self.L_apn/15
        I = []
        L_i = []
        D_i = []
        F_i = []
        Fkr_Fi = []
        lambda_i = []
        lambda_i.append(0.00430541215799347) #lambda???
        lambda_i.append(0.00645568875303399)
        lambda_i.append(0.0107357096097859)
        lambda_i.append(0.0212703247274636)
        lambda_i.append(0.0606711295853747)
        lambda_i.append(1.00012312002336)
        lambda_i.append(1.8142175853707)
        lambda_i.append(2.05543777829136)
        lambda_i.append(2.20149920640802)
        lambda_i.append(2.30325999877438)
        lambda_i.append(2.37968870285231)
        lambda_i.append(2.43992742650647)
        lambda_i.append(2.48904644589257)
        lambda_i.append(2.53012465846536)
        lambda_i.append(2.56516135150798)
        lambda_i.append(2.59551971001575)
        lambda_i.append(2.62216431201877)
        lambda_i.append(2.64580404266828)
        lambda_i.append(2.66696809416625)
        lambda_i.append(2.68606396712451)
        lambda_i.append(2.70341374219393)
        gdf_qu_l = []
        gdf_pi_l = []
        gdf_tau_l = []
        gdf_eps_l = []
        diff_q_Fkr = []
        P_ = []#wervjwjervkwcevkwclkwscowkeocwoeckwkeock viwe ewe
        T = []
        R_0 = []
        v = []
        for i in range(21):
            I.append(-5 + i)
            if I[i]  < 0 :
                L_i.append(self.X_bpn * I[i])
                x_Di = self.Dkr + ((self.D10_ - self.Dkr)/5)*(-I[i])
            else:
                L_i.append(X_apn * I[i])
                x_Di = self.Dkr + ((self.Da - self.Dkr)/15)*(I[i])
            D_i.append(x_Di)
            x_Fi = self.PI*(D_i[i]**2/4)
            F_i.append(x_Fi)
            Fkr_Fi.append(self.Fkr/F_i[i])
            x_gdf = calc_gdf_qu(lambda_i[i], self.k)
            gdf_qu_l.append(x_gdf)
            x_gdf = calc_gdf_pi(lambda_i[i], self.k)
            gdf_pi_l.append(x_gdf)
            x_gdf = calc_gdf_Tau(lambda_i[i], self.k)
            gdf_tau_l.append(x_gdf)
            x_gdf = calc_gdf_esp(lambda_i[i], self.k)
            gdf_eps_l.append(x_gdf)
            x = gdf_qu_l[i] - Fkr_Fi[i]
            diff_q_Fkr.append(x)
            x = gdf_pi_l[i] * long(self.P_k)
            P_.append(long(x))
            x = self.Tk * gdf_tau_l[i]
            T.append(x)
            x = self.P_k/(self.specific_gas_const*self.Tk)*gdf_eps_l[i]
            R_0.append(x)
            x = self.Akr * lambda_i[i]
            v.append(x)

    def print_initial_data(self):
        print("\\begin{center}")
        print("\\begin{tabular}{  | c | c | c | c | c | c | c | }")
        print("\\hline")
        print("Parameter & Value & Dimension & Index & Designation & Size & SI \\\\")
        print("\\hline")
        print("\\multicolumn{6}{|c}{Dimensions charge} & \\\\")
        print("\\hline")
        print '%s & %f & %s & %d & %s & %f & %s \\\\' % ('Length', self.l1, 'm', self.idx_l1, 'L10', self.L10_, 'm')
        print '%s & %d & %s & %d & %s & %d & %s \\\\' % (' ', self.l2, 'm', self.idx_l2, 'L20', self.L20_, 'm')
        print("\\hline")
        print '%s & %f & %s & %d & %s & %f & %s \\\\' % ('Diam', self.d1, 'm', self.idx_d1, 'D10', self.D10_, 'm')
        print '%s & %f & %s & %d & %s & %f & %s \\\\' % (' ', self.d2, 'm', self.idx_d2, 'D20', self.D20_, 'm')
        print '%s & %f & %s & %d & %s & %f & %s \\\\' % (' ', self.d3, 'm', self.idx_d3, 'D30', self.D30_, 'm')
        print("\\hline")
        print("\\multicolumn{6}{|c}{Data on fuel and combustion products} & \\\\")
        print("\\hline")
        print '%s & %d & %s & %d & %s & %f & %s \\\\' % ('The burning rate', self.speed_burn, 'mm/s', self.idx_speed_burn, 'u', self.u, 'm/s')
        print("\\hline")
        print '%s & %f & %s & %d & %s & %f & %s \\\\' % ('The index rate', self.burning_rate, ' - ', self.idx_burning_rate, '$\\nu$', self.nu, ' - ')
        print("\\hline")
        print '%s & %d & %s & %d & %s & %d & %s \\\\' % ('The base pressure for the unit speed', self.base_pressure, 'Pascal', self.idx_base_pressure, '$P_0$', self.P0, 'Pascal')
        print("\\hline")
        print '%s & %f & %s & %d & %s & %f & %s \\\\' % ( 'Indicator isentrope combustion', self.ind_isentrope, ' - ', self.idx_ind_isentrope, 'k', self.k, ' - ')
        print("\\hline")
        print '%s & %d & %s & %d & %s & %d & %s \\\\' % (
'Calculated value of the pressure in the CC', self.estimated_pressure_cc, 'MPascal',
self.idx_estimated_pressure_cc, '$P_k$', self.P_k, 'Pascal')
        print("\\hline")
        print '%s & %d & %s & %d & %s & %d & %s \\\\' % (
'Estimated value of the pressure at the nozzle exit', self.estimated_pressure_ne, 'kPascal',
self.idx_estimated_pressure_ne, '$P_a$', self.Pa, 'Pascal')
        print("\\hline")
        print '%s & %d & %s & %d & %s & %d & %s \\\\' % (
'The temperature in the combustion chamber', self.temp_cc, 'K', self.idx_temp_cc, '$T_k$', self.Tk, 'K')
        print("\\hline")
        print '%s & %d & %s & %d & %s & %d & %s \\\\' % (
'Molar Mass', self.molar_mass_ps, 'mole', self.idx_molar_mass_ps, '$\\mu$', self.mu, 'mole')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % (
'The specific gas constant', '', '', '', '$R_{spec}$', self.specific_gas_const, 'J/(kg*K)')
        print("\\hline")
        print '%s & %d & %s & %d & %s & %d & %s \\\\' % (
'Fuel Density', self.fuel_density, 'kg/$m^3$', self.idx_fuel_density, '$\\rho$', self.rho, 'kg/$m^3$')
        print("\\hline")
        print '%s & %f & %s & %d & %s & %f & %s \\\\' % ('The time step', self.time_step, ' - ', self.idx_time_step, 'h', self.h, ' ')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % ('Consumables complex', '', '', '', '$\\beta$', self.betta, ' ')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % ('Critical speed of sound', '', '', '', '$A_{kr}$', self.Akr, ' ')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % ('Throat area', '', '', '', '$F_{kr}$', self.Fkr, '$m^2$')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % (
'The diameter of the critical cross-section', '', '', '', '$D_{kr}$', self.Dkr, ' ')
        print("\\hline")
        print("\\multicolumn{6}{|c}{The geometry of the subsonic part of the nozzle: conical} & \\\\")
        print("\\hline")
        print '%s & %d & %s & %s & %s & %f & %s \\\\' % ('Angle', self.agle1, 'grade', '', '$\\phi_1$', self.phi1, 'radians')
        print("\\hline")
        print("\\multicolumn{6}{|c}{The geometry of the supersonic part of the nozzle: conical} & \\\\")
        print("\\hline")
        print '%s & %d & %s & %s & %s & %f & %s \\\\' % ('Angle', self.agle2, 'grade', '', '$\\phi_2$', self.phi2, 'radians')
        print("\\hline")
        print("\\end{tabular}")

    def print_calculated_data(self):
        print("\\begin{center}")
        print("\\textbf{\\textit{The calculated data}}\\\\")
        print("\\end{center}")

        print("\\begin{flushright}")
        print("\\textit{Table $N^o 3$: The calculated data}\\\\")
        print("\\end{flushright}")
        print("\\begin{tabular}{  | c | p{1.5cm} | p{1.5cm} | p{1.5cm} | c | c | p{1.5cm} | }")
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % ('The diameter at the nozzle exit', '', '', '', '$D_a$', self.Da, 'm')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % ('Cross-sectional area at the nozzle exit', '', '', '', '$F_a$', self.Fa, '$m^2$')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % ('Area ratio', '', '', '', 'Fkr/Fa', self.Fkr_Fa, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
        ('Maximum dimensionless speed', '', '', '', '$\\lambda_{max}$', self.lambda_max, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
        ('The dimensionless speed', '', '', '', '$\\lambda$', self.lambda_, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
        ('Speed at the nozzle exit', '', '', '', '$\\nu_a$', self.va, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
        ('Gas-dynamic functions', '', '', '', '$\\pi(\\lambda$)', self.gdf_pi, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
        ('Gas-dynamic functions', '', '', '', '$\\varepsilon(\\lambda$)', self.gdf_eps, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
        ('Gas-dynamic functions', '', '', '', 'q($\\lambda$)', self.gdf_qu, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
        ('The difference to the PI(lambda * a) - Pa / Pk', '', '', '', '', self.diff1, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
        ('The difference to the qu(lambda * a) - Fkr / Fa', '', '', '', '', self.diff2, '-')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s \\\\' % \
        ('The length of the subsonic part of the nozzle', '', '', '', '$L_{bpn}$', self.L_bpn, 'm')
        print("\\hline")
        print '%s & %s & %s & %s & %s & %f & %s  \\\\' % \
        ('The length of the supersonic part of the nozzle', '', '', '', '$L_{apn}$', self.L_apn, 'm')
        print("\\hline")
        print("\\end{tabular} ")
        print("\\end{center}")

    def print_dimensioning(self):
        print("\\newpage")

        print("\\begin{center}")
        print("\\textbf{\\textit{Dimensioning for quasi-stationary mode}}\\\\")
        print("\\end{center}")

        print("\\begin{flushright}")
        print("\\textit{Table $N^o 3$: The calculated data}\\\\")
        print("\\end{flushright}")
        print("\\tiny")
        print("\\renewcommand{\\arraystretch}{1} %% increase table row spacing")
        print("\\renewcommand{\\tabcolsep}{0.08cm}")
        print("\\begin{tabular}{|l*{18}{l|}}")
        print("\\hline")
        print '%s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s  \\\\' % ('t', 'li', '\(D_{20}\)', '\(D_{30}\)', '\(L_{10}\)', '\(L_{20}\)' , '\(L_{30}\)', '\(S_{10}\)', '\(S_{20}\)', '\(S_{30}\)', '\(S_{40}\)', 'Sg', 'pk', '\(G_c\)', 'pa', '\(I_{spec}\)', 'P', '\(u_{Pk}\)')
        print("\\hline")
        for i in range(63):
            print '%f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %d & %f & %f & %f & %f & %f \\\\' % (self.t[i], self.li[i], self.D20[i], self.D30[i], self.L10[i], self.L20[i] , self.L30[i], self.S10_[i], self.S20_[i] , self.S30_[i], self.S40_[i], self.Sg[i], self.pk[i], self.Gc[i], self.pa[i], self.I_spec[i], self.P[i], self.u_Pk[i] )
        print("\\hline")
        print("\\end{tabular}\\\\")
        print("\\begin{tabular}{|l*{18}{l|}}")
        print("\\hline")
        print '%s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s  \\\\' % ('t', 'li', '\(D_{20}\)', '\(D_{30}\)', '\(L_{10}\)', '\(L_{20}\)' , '\(L_{30}\)', '\(S_{10}\)', '\(S_{20}\)', '\(S_{30}\)', '\(S_{40}\)', 'Sg', 'pk', '\(G_c\)', 'pa', '\(I_{spec}\)', 'P', '\(u_{Pk}\)')
        print("\\hline")
        for i in range(67):
            print '%f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %d & %f & %f & %f & %f & %f \\\\' % (self.t[i + 63], self.li[i + 63], self.D20[i + 63], self.D30[i + 63], self.L10[i + 63], self.L20[i + 63], self.L30[i + 63], self.S10_[i + 63], self.S20_[i + 63], self.S30_[i + 63], self.S40_[i + 63], self.Sg[i + 63], self.pk[i + 63], self.Gc[i + 63], self.pa[i + 63], self.I_spec[i + 63], self.P[i + 63], self.u_Pk[i + 63])
        print("\\hline")
        print("\\end{tabular}")
        print("\\begin{tabular}{|l*{18}{l|}}")
        print("\\hline")
        print '%s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s  \\\\' % ('t', 'li', '\(D_{20}\)', '\(D_{30}\)', '\(L_{10}\)', '\(L_{20}\)' , '\(L_{30}\)', '\(S_{10}\)', '\(S_{20}\)', '\(S_{30}\)', '\(S_{40}\)', 'Sg', 'pk', '\(G_c\)', 'pa', '\(I_{spec}\)', 'P', '\(u_{Pk}\)')
        print("\\hline")
        for i in range(66):
            print '%f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %d & %f & %f & %f & %f & %f \\\\' % (self.t[i + 130], self.li[i + 130], self.D20[i + 130], self.D30[i + 130], self.L10[i + 130], self.L20[i + 130], self.L30[i + 130], self.S10_[i + 130], self.S20_[i + 130], self.S30_[i + 130], self.S40_[i + 130], self.Sg[i + 130], self.pk[i + 130], self.Gc[i + 130], self.pa[i + 130], self.I_spec[i + 130], self.P[i + 130], self.u_Pk[i + 130])
        print("\\hline")
        print("\\end{tabular}")
        print("\\begin{tabular}{|l*{18}{l|}}")
        #p{1.5cm}
        print("\\hline")
        print '%s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s & %s  \\\\' % ('t', 'li', '\(D_{20}\)', '\(D_{30}\)', '\(L_{10}\)', '\(L_{20}\)' , '\(L_{30}\)', '\(S_{10}\)', '\(S_{20}\)', '\(S_{30}\)', '\(S_{40}\)', 'Sg', 'pk', '\(G_c\)', 'pa', '\(I_{spec}\)', 'P', '\(u_{Pk}\)')
        print("\\hline")
        for i in range(5):
            print '%f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %f & %d & %f & %f & %f & %f & %f \\\\' % (self.t[i + 196], self.li[i + 196], self.D20[i + 196], self.D30[i + 196], self.L10[i + 196], self.L20[i + 196], self.L30[i + 196], self.S10_[i + 196], self.S20_[i + 196], self.S30_[i + 196], self.S40_[i + 196], self.Sg[i + 196], self.pk[i + 196], self.Gc[i + 196], self.pa[i + 196], self.I_spec[i + 196], self.P[i + 196], self.u_Pk[i + 196])
        print("\\hline")
        print("\\end{tabular}\\\\")

    def print_graphics(self):
        print("\\begin{center}")
        print("\\begin{large}")
        print("\\textbf{\\textit {Graphs}}\\\\")
        print("\\end{large}")
        print("\\end{center}")

        print("Tipo graphic 2 \\\\")
        print("\\begin{tikzpicture}")
        print("\\begin{axis}")
        print("\\addplot coordinates {")
        print("( 338.1, 2 )")
        print("( 169.1, 1 )")
        print("( 84.5, 6)")
        print("( 555, 5 )")
        print("( 21.1, 9 )};")
        print("\\end{axis}")
        print("\\end{tikzpicture}")
        print("\\begin{flushright}")
        print("\\textit{Pic. $N^o 2$: Changing the diameter of the charge during engine operation}\\\\")
        print("\\end{flushright}")

        print("Tipo graphic 3 \\\\")
        print("\\begin{flushright}")
        print("\\textit{Pic. $N^o 3$: Changing the length of the charge during engine operation}\\\\")
        print("\\end{flushright}")

        print("Tipo graphic 4 \\\\")
        print("\\begin{flushright}")
        print("\\textit{Pic. $N^o 4$: Changes in consumption during engine operation}\\\\")
        print("\\end{flushright}")

        print("Tipo graphic 5 \\\\")
        print("\\begin{flushright}")
        print("\\textit{Pic. $N^o 5$: Changing the burning area of the charge during engine operation}\\\\")
        print("\\end{flushright}")

        print("Tipo graphic 6 \\\\")
        print("\\begin{flushright}")
        print("\\textit{Pic. $N^o 6$: The change in pressure in the combustion chamber while the engine}\\\\")
        print("\\end{flushright}")

        print("Tipo graphic 7 \\\\")
        print("\\begin{flushright}")
        print("\\textit{Pic. $N^o 7$: Changing the speed of the combustion of fuel during engine operation}\\\\")
        print("\\end{flushright}")

        print("Tipo graphic 8 \\\\")
        print("\\begin{flushright}")
        print("\\textit{Pic. $N^o 8$: Change thrust during engine operation}\\\\")
        print("\\end{flushright}")

        print("Tipo graphic 9 \\\\")
        print("\\begin{flushright}")
        print("\\textit{Pic. $N^o 9$: Changing specific impulse while the engine}\\\\")
        print("\\end{flushright}")

    def print_constr_model_combustion(self):
        print("\\begin{center}")
        print("\\begin{large}")
        print("\\textbf{\\textit {Burning charge}}\\\\")
        print("\\end{large}")
        print("\\end{center}")

        print("\\begin{flushright}")
        print("\\textit{Table $N^o 4$: Table calculated data to construct a model of the engine combustion charge\\\\Table data validation through the function IF}\\\\")
        print("\\end{flushright}")

def main():
    calc_course = CalcCourseWork()
    calc_course.calc_data()
    calc_course.print_initial_data()
    calc_course.print_calculated_data()
    calc_course.print_dimensioning()
    calc_course.print_graphics()
    calc_course.print_constr_model_combustion()

if __name__ == '__main__':
    main()
