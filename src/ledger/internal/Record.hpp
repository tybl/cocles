#ifndef COCLES_LEDGER_INTERNAL_RECORD_HPP
#define COCLES_LEDGER_INTERNAL_RECORD_HPP

namespace ledger {

namespace internal {

struct Record {
   Record();

   explicit Record(bool available);

   void set_available(bool available);

   bool is_available() const;

private:
   bool m_is_available;
};

} // namespace internal

} // namespace ledger
#endif // COCLES_LEDGER_INTERNAL_RECORD_HPP
