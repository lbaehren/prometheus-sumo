
Importing a new (external) database    {#database_import}
===================================

\tableofcontents

The import of a new database is channeled through the generation and subsequent
reading of an \ref xml schema; the latter is either provided directly by the
maintainer(s) of the external database, or generated from e.g. a SQL dump of the
original database.

\section pandora_database_xml XML schema for the original data

\verbatim
<?xml version="1.0" encoding="UTF-8"?>
  <dataroot>
    <row>
      <bild_nr>G8001</bild_nr>
      <datierung>1783-1786</datierung>
      <gattung>Gartenarchitektur</gattung>
      <inventar_nr>GS 6258</inventar_nr>
      <kuenstler>Jussow, Heinrich Christoph (Zeichner)</kuenstler>
      <objekt>Tempel</objekt>
      <objekt_id>11846</objekt_id>
      <titel>Entwurf zu einem Gartentempel, Aufriß</titel>
    </row>
    <row>
      <bild_nr>G8002</bild_nr>
      <datierung>1783-1786</datierung>
      <gattung>Private Architektur</gattung>
      <inventar_nr>GS 6251</inventar_nr>
      <kuenstler>Jussow, Heinrich Christoph (Zeichner)</kuenstler>
      <objekt>Villa</objekt>
      <objekt_id>11839</objekt_id>
      <titel>Entwurf zu einer Villa, Grund- und Aufriß der Gartenfassade</titel>
    </row>
\endverbatim

\section pandora_database_model Source model

Models or new sources can be found in

\verbatim
  pandora
  `-- app/models
          |-- source
          |   |-- amtub.rb
          |   |-- arachne.rb
          |   |-- archgiessen.rb
          |   |..
          |-- source.rb
          `-- xml_source.rb
\endverbatim

Once the \ref xml schema for the new data is available, the information can be
accessible to \ref pandora

  \verbatim
    class Source

      class Kassel < XMLSource::Document

        def self.persist
          %w[bild_nr inventar_nr]
        end

        module Record

          def path
            "#{self/'bild_nr'}.jpg"
          end

          def d_artist
            self/'kuenstler'
          end

          def artists_for_vgbk
            ["#{self/'kuenstler'}".sub(/ \(.*/, '').split(', ').reverse.join(' ')]
          end
  \endverbatim
