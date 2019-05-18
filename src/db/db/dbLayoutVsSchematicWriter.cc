
/*

  KLayout Layout Viewer
  Copyright (C) 2006-2019 Matthias Koefferlein

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

*/

#include "dbLayoutVsSchematicWriter.h"
#include "dbLayoutVsSchematic.h"
#include "dbLayoutVsSchematicFormatDefs.h"

namespace db
{

// -------------------------------------------------------------------------------------------
//  LayoutVsSchematicWriterBase implementation

LayoutVsSchematicWriterBase::LayoutVsSchematicWriterBase ()
{
  //  .. nothing yet ..
}

LayoutVsSchematicWriterBase::~LayoutVsSchematicWriterBase ()
{
  //  .. nothing yet ..
}

void LayoutVsSchematicWriterBase::write (const db::LayoutVsSchematic *l2n)
{
  do_write (l2n);
}

#if 0
// -------------------------------------------------------------------------------------------

namespace l2n_std_format
{

// -------------------------------------------------------------------------------------------
//  std_writer_impl<Keys> implementation

template <class Keys>
class std_writer_impl
{
public:
  std_writer_impl (tl::OutputStream &stream);

  void write (const db::LayoutVsSchematic *l2n);

private:
  tl::OutputStream *mp_stream;
  db::Point m_ref;

  void write (const db::LayoutVsSchematic *l2n, const db::Circuit &circuit);
  void write (const db::LayoutVsSchematic *l2n, const db::Net &net, unsigned int id);
  void write (const db::LayoutVsSchematic *l2n, const db::SubCircuit &subcircuit, std::map<const Net *, unsigned int> &net2id);
  void write (const db::LayoutVsSchematic *l2n, const db::Device &device, std::map<const Net *, unsigned int> &net2id);
  void write (const db::LayoutVsSchematic *l2n, const db::DeviceAbstract &device_abstract);
  void write (const db::PolygonRef *s, const db::ICplxTrans &tr, const std::string &lname, bool relative);
  void reset_geometry_ref ();
};

static const std::string endl ("\n");
static const std::string indent1 (" ");
static const std::string indent2 ("  ");

template <class Keys>
std_writer_impl<Keys>::std_writer_impl (tl::OutputStream &stream)
  : mp_stream (&stream)
{
  //  .. nothing yet ..
}

static std::string name_for_layer (const db::LayoutVsSchematic *l2n, unsigned int l)
{
  std::string n = l2n->name (l);
  if (n.empty ()) {
    n = "L" + tl::to_string (l);
  }
  return n;
}

template <class Keys>
void std_writer_impl<Keys>::write (const db::LayoutVsSchematic *l2n)
{
  bool any = false;

  const int version = 0;

  const db::Layout *ly = l2n->internal_layout ();
  const db::Netlist *nl = l2n->netlist ();

  *mp_stream << "#%l2n-klayout" << endl;

  if (! Keys::is_short ()) {
    *mp_stream << endl << "# General section" << endl << endl;
  }

  if (version > 0) {
    *mp_stream << Keys::version_key << "(" << version << ")" << endl;
  }
  *mp_stream << Keys::top_key << "(" << tl::to_word_or_quoted_string (ly->cell_name (l2n->internal_top_cell ()->cell_index ())) << ")" << endl;
  *mp_stream << Keys::unit_key << "(" << ly->dbu () << ")" << endl;

  if (! Keys::is_short ()) {
    *mp_stream << endl << "# Layer section" << endl;
    *mp_stream << "# This section lists the mask layers (drawing or derived) and their connections." << endl;
  }

  if (! Keys::is_short ()) {
    *mp_stream << endl << "# Mask layers" << endl;
  }
  for (db::Connectivity::layer_iterator l = l2n->connectivity ().begin_layers (); l != l2n->connectivity ().end_layers (); ++l) {
    *mp_stream << Keys::layer_key << "(" << name_for_layer (l2n, *l);
    db::LayerProperties lp = ly->get_properties (*l);
    if (! lp.is_null ()) {
      *mp_stream << " " << tl::to_word_or_quoted_string (lp.to_string ());
    }
    *mp_stream << ")" << endl;
  }

  if (! Keys::is_short ()) {
    *mp_stream << endl << "# Mask layer connectivity" << endl;
  }
  for (db::Connectivity::layer_iterator l = l2n->connectivity ().begin_layers (); l != l2n->connectivity ().end_layers (); ++l) {

    db::Connectivity::layer_iterator ce = l2n->connectivity ().end_connected (*l);
    db::Connectivity::layer_iterator cb = l2n->connectivity ().begin_connected (*l);
    if (cb != ce) {
      *mp_stream << Keys::connect_key << "(" << name_for_layer (l2n, *l);
      for (db::Connectivity::layer_iterator c = l2n->connectivity ().begin_connected (*l); c != ce; ++c) {
        *mp_stream << " " << name_for_layer (l2n, *c);
      }
      *mp_stream << ")" << endl;
    }

  }

  any = false;
  for (db::Connectivity::layer_iterator l = l2n->connectivity ().begin_layers (); l != l2n->connectivity ().end_layers (); ++l) {

    db::Connectivity::global_nets_iterator ge = l2n->connectivity ().end_global_connections (*l);
    db::Connectivity::global_nets_iterator gb = l2n->connectivity ().begin_global_connections (*l);
    if (gb != ge) {
      if (! any) {
        if (! Keys::is_short ()) {
          *mp_stream << endl << "# Global nets and connectivity" << endl;
        }
        any = true;
      }
      *mp_stream << Keys::global_key << "(" << name_for_layer (l2n, *l);
      for (db::Connectivity::global_nets_iterator g = gb; g != ge; ++g) {
        *mp_stream << " " << tl::to_word_or_quoted_string (l2n->connectivity ().global_net_name (*g));
      }
      *mp_stream << ")" << endl;
    }

  }

  if (nl->begin_device_classes () != nl->end_device_classes () && ! Keys::is_short ()) {
    *mp_stream << endl << "# Device class section" << endl;
    for (db::Netlist::const_device_class_iterator c = nl->begin_device_classes (); c != nl->end_device_classes (); ++c) {
      db::DeviceClassTemplateBase *temp = db::DeviceClassTemplateBase::is_a (c.operator-> ());
      if (temp) {
        *mp_stream << Keys::class_key << "(" << tl::to_word_or_quoted_string (c->name ()) << " " << tl::to_word_or_quoted_string (temp->name ()) << ")" << endl;
      }
    }
  }

  if (nl->begin_device_abstracts () != nl->end_device_abstracts () && ! Keys::is_short ()) {
    *mp_stream << endl << "# Device abstracts section" << endl;
    *mp_stream << "# Device abstracts list the pin shapes of the devices." << endl;
  }
  for (db::Netlist::const_abstract_model_iterator m = nl->begin_device_abstracts (); m != nl->end_device_abstracts (); ++m) {
    if (m->device_class ()) {
      *mp_stream << Keys::device_key << "(" << tl::to_word_or_quoted_string (m->name ()) << " " << tl::to_word_or_quoted_string (m->device_class ()->name ()) << endl;
      write (l2n, *m);
      *mp_stream << ")" << endl;
    }
  }

  if (! Keys::is_short ()) {
    *mp_stream << endl << "# Circuit section" << endl;
    *mp_stream << "# Circuits are the hierarchical building blocks of the netlist." << endl;
  }
  for (db::Netlist::const_bottom_up_circuit_iterator i = nl->begin_bottom_up (); i != nl->end_bottom_up (); ++i) {
    const db::Circuit *x = *i;
    *mp_stream << Keys::circuit_key << "(" << tl::to_word_or_quoted_string (x->name ()) << endl;
    write (l2n, *x);
    *mp_stream << ")" << endl;
  }
}

template <class Keys>
void std_writer_impl<Keys>::write (const db::LayoutVsSchematic *l2n, const db::Circuit &circuit)
{
  std::map<const db::Net *, unsigned int> net2id;
  unsigned int id = 0;

  if (circuit.begin_nets () != circuit.end_nets ()) {
    if (! Keys::is_short ()) {
      *mp_stream << endl << indent1 << "# Nets with their geometries" << endl;
    }
    for (db::Circuit::const_net_iterator n = circuit.begin_nets (); n != circuit.end_nets (); ++n) {
      net2id.insert (std::make_pair (n.operator-> (), ++id));
      write (l2n, *n, id);
    }
  }

  if (circuit.begin_pins () != circuit.end_pins ()) {
    if (! Keys::is_short ()) {
      *mp_stream << endl << indent1 << "# Outgoing pins and their connections to nets" << endl;
    }
    for (db::Circuit::const_pin_iterator p = circuit.begin_pins (); p != circuit.end_pins (); ++p) {
      const db::Net *net = circuit.net_for_pin (p->id ());
      if (net) {
        *mp_stream << indent1 << Keys::pin_key << "(" << tl::to_word_or_quoted_string (p->expanded_name ()) << " " << net2id [net] << ")" << endl;
      }
    }
  }

  if (circuit.begin_devices () != circuit.end_devices ()) {
    if (! Keys::is_short ()) {
      *mp_stream << endl << indent1 << "# Devices and their connections" << endl;
    }
    for (db::Circuit::const_device_iterator d = circuit.begin_devices (); d != circuit.end_devices (); ++d) {
      write (l2n, *d, net2id);
    }
  }

  if (circuit.begin_subcircuits () != circuit.end_subcircuits ()) {
    if (! Keys::is_short ()) {
      *mp_stream << endl << indent1 << "# Subcircuits and their connections" << endl;
    }
    for (db::Circuit::const_subcircuit_iterator x = circuit.begin_subcircuits (); x != circuit.end_subcircuits (); ++x) {
      write (l2n, *x, net2id);
    }
  }

  if (! Keys::is_short ()) {
    *mp_stream << endl;
  }
}

void write_point (tl::OutputStream &stream, const db::Point &pt, db::Point &ref, bool relative)
{
  if (relative) {

    stream << "(";
    stream << pt.x () - ref.x ();
    stream << " ";
    stream << pt.y () - ref.y ();
    stream << ")";

  } else {

    if (pt.x () == 0 || pt.x () != ref.x ()) {
      stream << pt.x ();
    } else {
      stream << "*";
    }

    if (pt.y () == 0 || pt.y () != ref.y ()) {
      stream << pt.y ();
    } else {
      stream << "*";
    }

  }

  ref = pt;
}

template <class T, class Tr>
void write_points (tl::OutputStream &stream, const T &poly, const Tr &tr, db::Point &ref, bool relative)
{
  for (typename T::polygon_contour_iterator c = poly.begin_hull (); c != poly.end_hull (); ++c) {

    typename T::point_type pt = tr * *c;

    stream << " ";
    write_point (stream, pt, ref, relative);

  }
}

template <class Keys>
void std_writer_impl<Keys>::reset_geometry_ref ()
{
  m_ref = db::Point ();
}

template <class Keys>
void std_writer_impl<Keys>::write (const db::PolygonRef *s, const db::ICplxTrans &tr, const std::string &lname, bool relative)
{
  db::ICplxTrans t = tr * db::ICplxTrans (s->trans ());

  const db::Polygon &poly = s->obj ();
  if (poly.is_box ()) {

    db::Box box = t * poly.box ();
    *mp_stream << Keys::rect_key << "(" << lname;
    *mp_stream << " ";
    write_point (*mp_stream, box.p1 (), m_ref, relative);
    *mp_stream << " ";
    write_point (*mp_stream, box.p2 (), m_ref, relative);
    *mp_stream << ")";

  } else {

    *mp_stream << Keys::polygon_key << "(" << lname;
    if (poly.holes () > 0) {
      db::SimplePolygon sp (poly);
      write_points (*mp_stream, sp, t, m_ref, relative);
    } else {
      write_points (*mp_stream, poly, t, m_ref, relative);
    }
    *mp_stream << ")";

  }
}

template <class Keys>
void std_writer_impl<Keys>::write (const db::LayoutVsSchematic *l2n, const db::Net &net, unsigned int id)
{
  if (! l2n->netlist ()) {
    throw tl::Exception (tl::to_string (tr ("Can't write annotated netlist before extraction has been done")));
  }

  const db::hier_clusters<db::PolygonRef> &clusters = l2n->net_clusters ();
  const db::Circuit *circuit = net.circuit ();
  const db::Connectivity &conn = l2n->connectivity ();

  bool any = false;

  reset_geometry_ref ();

  for (db::Connectivity::layer_iterator l = conn.begin_layers (); l != conn.end_layers (); ++l) {

    db::cell_index_type cci = circuit->cell_index ();
    db::cell_index_type prev_ci = cci;

    for (db::recursive_cluster_shape_iterator<db::PolygonRef> si (clusters, *l, cci, net.cluster_id ()); ! si.at_end (); ) {

      //  NOTE: we don't recursive into circuits which will later be output. However, as circuits may
      //  vanish in "purge" but the clusters will still be there we need to recursive into clusters from
      //  unknown cells.
      db::cell_index_type ci = si.cell_index ();
      if (ci != prev_ci && ci != cci && (l2n->netlist ()->circuit_by_cell_index (ci) || l2n->netlist ()->device_abstract_by_cell_index (ci))) {

        si.skip_cell ();

      } else {

        if (! any) {
          *mp_stream << indent1 << Keys::net_key << "(" << id;
          if (! net.name ().empty ()) {
            *mp_stream << " " << Keys::name_key << "(" << tl::to_word_or_quoted_string (net.name ()) << ")";
          }
          *mp_stream << endl;
          any = true;
        }

        *mp_stream << indent2;
        write (si.operator-> (), si.trans (), name_for_layer (l2n, *l), true);
        *mp_stream << endl;

        prev_ci = ci;

        ++si;

      }

    }

  }

  if (any) {
    *mp_stream << indent1 << ")" << endl;
  } else {

    *mp_stream << indent1 << Keys::net_key << "(" << id;
    if (! net.name ().empty ()) {
      *mp_stream << " " << Keys::name_key << "(" << tl::to_word_or_quoted_string (net.name ()) << ")";
    }
    *mp_stream << ")" << endl;

  }
}

template <class Keys>
void std_writer_impl<Keys>::write (const db::LayoutVsSchematic *l2n, const db::SubCircuit &subcircuit, std::map<const Net *, unsigned int> &net2id)
{
  const db::Layout *ly = l2n->internal_layout ();
  double dbu = ly->dbu ();

  *mp_stream << indent1 << Keys::circuit_key << "(" << tl::to_word_or_quoted_string (subcircuit.expanded_name ());
  *mp_stream << " " << tl::to_word_or_quoted_string (subcircuit.circuit_ref ()->name ());

  const db::DCplxTrans &tr = subcircuit.trans ();
  if (tr.is_mag ()) {
    *mp_stream << " " << Keys::scale_key << "(" << tr.mag () << ")";
  }
  if (tr.is_mirror ()) {
    *mp_stream << " " << Keys::mirror_key;
  }
  if (fabs (tr.angle ()) > 1e-6) {
    *mp_stream << " " << Keys::rotation_key << "(" << tr.angle () << ")";
  }
  *mp_stream << " " << Keys::location_key << "(" << tr.disp ().x () / dbu << " " << tr.disp ().y () / dbu << ")";

  //  each pin in one line for more than a few pins
  bool separate_lines = (subcircuit.circuit_ref ()->pin_count () > 1);

  if (separate_lines) {
    *mp_stream << endl;
  }

  for (db::Circuit::const_pin_iterator p = subcircuit.circuit_ref ()->begin_pins (); p != subcircuit.circuit_ref ()->end_pins (); ++p) {
    const db::Net *net = subcircuit.net_for_pin (p->id ());
    if (net) {
      if (separate_lines) {
        *mp_stream << indent2;
      } else {
        *mp_stream << " ";
      }
      *mp_stream << Keys::pin_key << "(" << tl::to_word_or_quoted_string (p->expanded_name ()) << " " << net2id [net] << ")";
      if (separate_lines) {
        *mp_stream << endl;
      }
    }
  }

  if (separate_lines) {
    *mp_stream << indent1;
  }

  *mp_stream << ")" << endl;
}

template <class Keys>
void std_writer_impl<Keys>::write (const db::LayoutVsSchematic *l2n, const db::DeviceAbstract &device_abstract)
{
  const std::vector<db::DeviceTerminalDefinition> &td = device_abstract.device_class ()->terminal_definitions ();

  const db::hier_clusters<db::PolygonRef> &clusters = l2n->net_clusters ();
  const db::Connectivity &conn = l2n->connectivity ();

  for (std::vector<db::DeviceTerminalDefinition>::const_iterator t = td.begin (); t != td.end (); ++t) {

    *mp_stream << indent1 << Keys::terminal_key << "(" << t->name () << endl;

    reset_geometry_ref ();

    for (db::Connectivity::layer_iterator l = conn.begin_layers (); l != conn.end_layers (); ++l) {

      const db::local_cluster<db::PolygonRef> &lc = clusters.clusters_per_cell (device_abstract.cell_index ()).cluster_by_id (device_abstract.cluster_id_for_terminal (t->id ()));
      for (db::local_cluster<db::PolygonRef>::shape_iterator s = lc.begin (*l); ! s.at_end (); ++s) {

        *mp_stream << indent2;
        write (s.operator-> (), db::ICplxTrans (), name_for_layer (l2n, *l), true);
        *mp_stream << endl;

      }

    }

    *mp_stream << indent1 << ")" << endl;

  }
}

template <class Keys>
void std_writer_impl<Keys>::write (const db::LayoutVsSchematic *l2n, const db::Device &device, std::map<const Net *, unsigned int> &net2id)
{
  const db::Layout *ly = l2n->internal_layout ();
  double dbu = ly->dbu ();
  db::VCplxTrans dbu_inv (1.0 / dbu);

  tl_assert (device.device_class () != 0);
  const std::vector<DeviceTerminalDefinition> &td = device.device_class ()->terminal_definitions ();
  const std::vector<DeviceParameterDefinition> &pd = device.device_class ()->parameter_definitions ();

  *mp_stream << indent1 << Keys::device_key << "(" << tl::to_word_or_quoted_string (device.expanded_name ());

  tl_assert (device.device_abstract () != 0);
  *mp_stream << " " << tl::to_word_or_quoted_string (device.device_abstract ()->name ()) << endl;

  const std::vector<db::DeviceAbstractRef> &other_abstracts = device.other_abstracts ();
  for (std::vector<db::DeviceAbstractRef>::const_iterator a = other_abstracts.begin (); a != other_abstracts.end (); ++a) {

    db::Vector pos = dbu_inv * a->offset;

    *mp_stream << "  " << Keys::device_key << "(" << tl::to_word_or_quoted_string (a->device_abstract->name ()) << " " << pos.x () << " " << pos.y () << ")" << endl;

  }

  const std::map<unsigned int, std::vector<db::DeviceReconnectedTerminal> > &reconnected_terminals = device.reconnected_terminals ();
  for (std::map<unsigned int, std::vector<db::DeviceReconnectedTerminal> >::const_iterator t = reconnected_terminals.begin (); t != reconnected_terminals.end (); ++t) {

    for (std::vector<db::DeviceReconnectedTerminal>::const_iterator c = t->second.begin (); c != t->second.end (); ++c) {
      *mp_stream << "  " << Keys::connect_key << "(" << c->device_index << " " << tl::to_word_or_quoted_string (td [t->first].name ()) << " " << tl::to_word_or_quoted_string (td [c->other_terminal_id].name ()) << ")" << endl;
    }

  }

  db::Point pos = dbu_inv * device.position ();

  *mp_stream << indent2 << Keys::location_key << "(" << pos.x () << " " << pos.y () << ")" << endl;

  for (std::vector<DeviceParameterDefinition>::const_iterator i = pd.begin (); i != pd.end (); ++i) {
    *mp_stream << indent2 << Keys::param_key << "(" << tl::to_word_or_quoted_string (i->name ()) << " " << device.parameter_value (i->id ()) << ")" << endl;
  }

  for (std::vector<DeviceTerminalDefinition>::const_iterator i = td.begin (); i != td.end (); ++i) {
    const db::Net *net = device.net_for_terminal (i->id ());
    if (net) {
      *mp_stream << indent2 << Keys::terminal_key << "(" << tl::to_word_or_quoted_string (i->name ()) << " " << net2id [net] << ")" << endl;
    }
  }

  *mp_stream << indent1 << ")" << endl;
}

}
#endif

// -------------------------------------------------------------------------------------------
//  LayoutVsSchematicStandardWriter implementation

LayoutVsSchematicStandardWriter::LayoutVsSchematicStandardWriter (tl::OutputStream &stream, bool short_version)
  : mp_stream (&stream), m_short_version (short_version)
{
  //  .. nothing yet ..
}

void LayoutVsSchematicStandardWriter::do_write (const db::LayoutVsSchematic * /*lvs*/)
{
#if 0
  if (m_short_version) {
    l2n_std_format::std_writer_impl<l2n_std_format::keys<true> > writer (*mp_stream);
    writer.write (l2n);
  } else {
    l2n_std_format::std_writer_impl<l2n_std_format::keys<false> > writer (*mp_stream);
    writer.write (l2n);
  }
#endif
}

}
