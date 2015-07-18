# SerializeInSameWay

In usual, serialize/unserialize like this
void XXX::Serialize(archive& ar)
{
  if(ar.isloading()
  {
    //serialize
    ar << a;
    ar << b;
    ar << c;
  }
  else
  {
    //unserialize
    ar >> a;
    ar >> b;
    ar >> c;
  }
}

SerializeInSameWay implement like this:
void XXX::Serialize(DataStreamHelper& helper)
{
  helper & a & b & c;
}
