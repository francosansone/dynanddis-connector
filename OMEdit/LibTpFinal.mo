package LibTpFinal
package FileHandler
  model ValueReader
    Real x;
    Real A;
  equation
    x = ReadValue(A);
    A = Modelica.Math.sin(time);
  end ValueReader;

  function ReadValue
    input Real x;
    output Real y;
  
    external y = ReadLastValue(x) annotation(
      Library = "/home/fran/Workspace/dynwithdis-connector/OMEdit/flib");
  end ReadValue;

  function WriteValue
    input Real x;
    output Real y;
  
    external y = WriteLastValue(x) annotation(
      Library = "/home/fran/Workspace/dynwithdis-connector/OMEdit/flib");
  end WriteValue;

  model ValueWriter
    input Real x;
    output Real z;
    output Real A;
  equation
//    when sample(1.0, 1) then
    z = WriteValue(x);
    A = Modelica.Math.sin(time);
//    end when;
  end ValueWriter;
/*
  model NewSample
    Electrical.RL rl;
    ValueWriter valueWriter;
    ValueReader valueReader;
  equation
    connect(rl.rlopen.la.v, valueWriter.x);
    connect(rl.rlopen.va.v, valueReader.x);
  end NewSample;
*/
end FileHandler;

  package Electrical
    type Voltage = Real(unit = "V");
    type Current = Real(unit = "A");
  
    connector Pin
      Voltage v;
      flow Current i;
    end Pin;
  
    model ConstVoltage
      Pin p, n;
      Voltage V;
    equation
      p.v - n.v = V;
      p.i + n.i = 0;
    end ConstVoltage;
  
    model Ground
      Pin p;
    equation
      p.v = 0;
    end Ground;
  
    partial model OnePort
      Pin p, n;
      Voltage v;
      Current i;
    equation
      v = p.v - n.v;
      i = p.i;
      i = -n.i;
    end OnePort;
  
    model Resistor
      extends OnePort;
      parameter Voltage R = 1;
    equation
      v = R * i;
    end Resistor;
  
    model Inductor
      extends OnePort;
      parameter Voltage L = 1;
    equation
      L * der(i) = v;
    end Inductor;
  
    model RLOpen
      ConstVoltage va;
      Resistor ra;
      Inductor la(L = 0.001);
      Ground gr;
    equation
      connect(va.p, ra.p);
      connect(ra.n, la.p);
      connect(va.n, gr.p);
    end RLOpen;
  
    model RL
      RLOpen rlopen;
    equation
      connect(rlopen.la.n, rlopen.gr.p);
    end RL;
  end Electrical;

  package Rotational
    type Torque = Real(unit = "N.m");
    type Angle = Real(unit = "rad");
    type AngSpeed = Real(unit = "rad/s");
  
    connector Flange
      Angle th;
      flow Torque tau;
    end Flange;
  
    model Inertia
      //Flange flange;
      //AngSpeed w;
      extends PartialRot;
      parameter Real J = 1;
    equation
      J * der(w) = flange.tau;
  //der(flange.th)=w;
    end Inertia;
  
    model Friction
      extends PartialRot;
      parameter Real B = 2;
    equation
      flange.tau = B * w;
    end Friction;
  
    partial model PartialRot
      Flange flange;
      AngSpeed w;
    equation
      der(flange.th) = w;
    end PartialRot;
  
    model ConstTorque
      extends PartialRot;
      parameter Torque Tau = 1;
    equation
      flange.tau = -Tau;
    end ConstTorque;
  
    model FricInertia
      Inertia inertia;
      Friction friction;
    equation
      connect(inertia.flange, friction.flange);
    end FricInertia;
  
    model FricInertiaTau
      FricInertia fricInertia;
      ConstTorque constTorque;
    equation
      connect(fricInertia.inertia.flange, constTorque.flange);
    end FricInertiaTau;
  end Rotational;

  package ElectroMec
    model ElMecConv
      extends Electrical.OnePort;
      Rotational.Flange flange;
      Rotational.AngSpeed w;
      parameter Real K = 1;
      //ValueWriter valueWriter;
    equation
      flange.tau = -K * i;
      v = K * w;
      der(flange.th) = w;
      //valueWriter.x = ;
    end ElMecConv;

model DCMotor
  Electrical.RLOpen rlopen;
  Rotational.FricInertia fricintertia;
  ElMecConv emc;
  FileHandler.ValueReader valueReader;
  FileHandler.ValueWriter valueWriter;
equation
  connect(rlopen.va.V, valueReader.x);
  connect(emc.w, valueWriter.x);
  connect(rlopen.la.n, emc.p);
  connect(rlopen.gr.p, emc.n);
  connect(fricintertia.inertia.flange, emc.flange);
end DCMotor;
  end ElectroMec;
  annotation(
    uses(Modelica(version = "3.2.2")));
end LibTpFinal;