use WWW::Mechanize

$site = @ARGV[0];
$filetype = @ARGV[1];

$searchurl = "http://www.google.com/search?hl=en&q=site%3A$site+filetype%3A$filetype";

$mech = WWW::Mechanize->new();
$mech->agent_alias('Windows_Mozila');
$mech->get($searchurl);

@links = $mech->find_all_links(url_regex => qr/\d+.+\.$filetype/);

for $link (@links)
{
	$url = $link->url_abs;
	$filename = $url;
	$filename =~ s[.*/][];
	print "downloading $url\n";
	$mech->get($url, ':content_file' => $filename);
}










